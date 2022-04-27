#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int**dinamikmatrisolusturma(int satir,int sutun);//Dinamik olarak matris oluþturup geri döndüren fonksiyon
int randomsayi(int minimum,int maksimum);// minimum-maksimum arasý rastgele sayý üretip döndüren fonksiyon
void matrisdoldur(int**gelenmtrs,int satir,int sutun);//Gönderilen matrisin içinin rastgele sayýlarla doldurulduðu fonksiyon
void transpozdoldur(int**gelentranspoz,int**gelenmatris,int satir,int sutun);// matrisin transpozesini alýp baþka bir matrise atan fonksiyon
void matrisbubblesort(int**gelenmatris,int satir,int sutun);// Matristeki elemanlar buble sort algoritmasý ile sýralanýyor
void dosyayayazma(int**gelenmatris,int**gelentranspoz,int satir,int sutun);// matrisin normal ve transpoze halini dosyaya yazýyoruz.
int kacbasamakli(int sayi);
void ihtimalleridiziyeatma(int gelen,int basamaksayisi, int* gecicidizi);/*"basamaksayisi" "gelen" deðerin kaç basamaklý olduðunu tutar. 
gecici diziye "gelen" deðerin tüm 2 ye parçalanmýþ halllerinin toplamýný atýyoruz.(örneðin 88209 geldi 8+8209,88+209,882+09... deðerlerini
atýyoruz.). Bu sayede gecici dizinin herhangi bir elemanýnýn, matrisin o anki elemanýna(geçici=matrisin o an kontrol ettiðimiz deðerinin 
karesi) eþit olmasý durumunda matrisin o elemanýnýn kaprekar sayýsý olduðunu anlýyoruz.
(Bu fonksiyonu kaprekaryazdirma fonksiyonunda kullanýyoruz.) */

void kaprekaryazdirma(int**gelenmatris,int satir,int sutun);//matrisin deðerlerini tek tek kontrol ederek kaprekar sayý olanlarý dosyaya yazýyoruz
void matrisfreeleme(int **gelenmatris,int satir);//Ayýrdýðýmýz bellek alanlarýný geri iade ediyoruz.
int usal(int sayi,int us);
int main()
{
      int**matris,**transpozematris;
     int satirsayisi,sutunsayisi;
    srand(time(NULL));
    printf("matris kac satir olsun?");
    scanf("%d",&satirsayisi);
    printf("matris kac sutun olsun?");
    scanf("%d",&sutunsayisi);
    matris=dinamikmatrisolusturma(satirsayisi,sutunsayisi);
    matrisdoldur(matris,satirsayisi,sutunsayisi);
    matrisbubblesort(matris,satirsayisi,sutunsayisi);
    transpozematris=dinamikmatrisolusturma(sutunsayisi,satirsayisi);
    transpozdoldur(transpozematris,matris,satirsayisi,sutunsayisi);
    dosyayayazma(matris,transpozematris,satirsayisi,sutunsayisi);
    kaprekaryazdirma(matris,satirsayisi,sutunsayisi);
    matrisfreeleme(matris,satirsayisi);
    matrisfreeleme(transpozematris,sutunsayisi);
    fflush(stdin);
    getchar();
    return 0;
}
int**dinamikmatrisolusturma(int satir,int sutun)
{
       int**Matris,i;
       Matris=(int**)malloc(satir*sizeof(int));
    if(Matris==NULL)
        printf("Yetersiz bellek alaný");
    for(i=0;i<satir;i++)
    {
        Matris[i]=malloc(sutun*sizeof(int));
        if(Matris[i]==NULL)
        printf("Yetersiz bellek alaný");
    }
    return Matris;
}
int randomsayi(int minimum,int maksimum)
{
    return(minimum+rand()%(maksimum-minimum+1));
}
void matrisdoldur(int**gelenmtrs,int satir,int sutun)
{
	int i,j;
    for(i=0;i<satir;i++)
    {
        for(j=0;j<sutun;j++)
        {
            gelenmtrs[i][j]=randomsayi(5,40000);
        }
    }
}

void transpozdoldur(int**gelentranspoz,int**gelenmatris,int satir,int sutun)
{	int i,j;
    for(i=0;i<satir;i++)
    {
        for(j=0;j<sutun;j++) {
           gelentranspoz[j][i]=gelenmatris[i][j];
        }
    }
}
void matrisbubblesort(int**gelenmatris,int satir,int sutun)
{
    int gecici,i,h,j;
    for (i = 0; i < satir*sutun-1; i = i + 1)
    {
        for (j = 0; j < satir*sutun-1-i; j = j + 1)
        {
            if (gelenmatris[j/sutun][j%sutun] > gelenmatris[(j+1)/sutun][(j+1)%sutun])
            {
                gecici = gelenmatris[j/sutun][j%sutun];
                gelenmatris[j/sutun][j%sutun] = gelenmatris[(j+1)/sutun][(j+1)%sutun];
                gelenmatris[(j+1)/sutun][(j+1)%sutun] = gecici;
            }
        }
    }
}
void dosyayayazma(int**gelenmatris,int**gelentranspoz,int satir,int sutun)
{ int i,j;
    FILE*dosya;

    dosya=fopen("transpoze.txt","w+");
    if(dosya==NULL)
       {
        printf("Dosya Acilamadi!\n");
        exit(1);
       }
    fprintf(dosya,"Normal Hali\n");


    for( i=0;i<satir;i++)
    {
        for(j=0;j<sutun;j++)
        {
         fprintf(dosya,"%5d ",gelenmatris[i][j]);
        }
       fprintf(dosya,"\n");
    }


        fprintf(dosya,"Transpoze Hali\n");
           for( i=0;i<sutun;i++)
    {
        for(j=0;j<satir;j++)
        {
         fprintf(dosya,"%5d ",gelentranspoz[i][j]);
        }
       fprintf(dosya,"\n");
    }


printf("yazdirma islemi tamam!");
fclose(dosya);

}

int kacbasamakli(int sayi)
{ int sayac=0;

    while (sayi > 0)
        {

        sayi=sayi/10;
         sayac++;

    }
    return sayac;
}

void kaprekaryazdirma(int**gelenmatris,int satir,int sutun)
{
    int karesi,basamaksayisi,dizielemansayisi,matrisindegeri,izleyici=0,i,j,k;

    FILE*dosya;

    dosya=fopen("kaprekar.txt","w+");
    if(dosya==NULL)
    {
         printf("Dosya Acilamadi!\n");
        exit(1);
    }

    for(i=0;i<satir;i++)
    {
        for(j=0;j<sutun;j++)
        {
            matrisindegeri=gelenmatris[i][j];
            karesi=usal(matrisindegeri,2);
            basamaksayisi=kacbasamakli(karesi);
            int gecicidizi[basamaksayisi];
            ihtimalleridiziyeatma(karesi,basamaksayisi,gecicidizi);
            for(k=0;k<basamaksayisi;k++)
            {
                if(matrisindegeri==gecicidizi[k])
                {
                    fprintf(dosya, "\n %d", matrisindegeri);
                    izleyici++;
                }
            }
        }
    }
    if(izleyici==0)
        printf("\nKaprekar yok.");
    else
        printf("\n%d Adet kaprekar sayi bulundu.",izleyici);

    fclose(dosya);

}
void ihtimalleridiziyeatma(int gelen,int basamaksayisi, int *gecicidizi)
{
    int birincikisim,ikincikisim,usalma,i,incieleman=0;

    incieleman=0;
    for(i=basamaksayisi-1;i>0;i--)
    {

        usalma=usal(10,i);
        birincikisim=(gelen%usalma);
        ikincikisim=(gelen/usalma);
        if(birincikisim!=0&&ikincikisim!=0)
        {
            gecicidizi[incieleman]=birincikisim+ikincikisim;
            incieleman++;
        }

    }

}
int usal(int sayi,int us)
{ int s=1,i;
    for (i=0;i<us;i++)
    {
        s=s*sayi;
    }
    return s;
}
void matrisfreeleme(int **gelenmatris,int satir)
{
    int i;
    for(i = 0; i < satir; i++)
	{
	    free((int *) gelenmatris[i]);
	}
      free((int *) gelenmatris);
}







