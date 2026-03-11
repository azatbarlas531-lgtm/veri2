#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* YAPI (STRUCT): LogDugumu
* Amacý: Her bir Syslog satýrýný ve bir sonraki kayda olan baðlantýyý tutmak.
* Neden Baðlý Liste? Log sayýsý önceden bilinmediði için dinamik bellek yönetimi saðlar.
*/
typedef struct LogDugumu {
    char logIcerigi[1024];          // Log mesajýný saklayan metin dizisi
    struct LogDugumu* sonrakiNode;  // Listenin bir sonraki elemanýna iþaretçi
} LogDugumu;

/*
* FONKSÝYON: yeniLogOlustur
* Amacý: Bellekte (Heap) yeni bir yer ayýrarak içine log verisini yazar.
*/
LogDugumu* yeniLogOlustur(char* veri) {
    LogDugumu* yeniNode = (LogDugumu*)malloc(sizeof(LogDugumu));
    if (yeniNode == NULL) {
        printf("Kritik Hata: Bellek tahsis edilemedi!\n");
        return NULL;
    }
    // Veriyi güvenli bir þekilde kopyalýyoruz
    strncpy(yeniNode->logIcerigi, veri, 1024);
    yeniNode->sonrakiNode = NULL;
    return yeniNode;
}

/*
* FONKSÝYON: logListesineEkle
* Amacý: Gelen yeni log kaydýný Tek Yönlü Baðlý Liste'nin sonuna ekler.
*/
void logListesineEkle(LogDugumu** baslangic, char* veri) {
    LogDugumu* yeniNode = yeniLogOlustur(veri);
    if (*baslangic == NULL) {
        *baslangic = yeniNode;
        return;
    }
   
    LogDugumu* gecici = *baslangic;
    while (gecici->sonrakiNode != NULL) {
        gecici = gecici->sonrakiNode;
    }
    gecici->sonrakiNode = yeniNode;
}

/*
* FONKSÝYON: tumLoglariGoster
* Amacý: Baðlý listedeki tüm düðümleri sýrasýyla ekrana yazdýrýr (Demo için).
*/
void tumLoglariGoster(LogDugumu* kafa) {
    LogDugumu* suanki = kafa;
    int sayac = 1;
    printf("\n--- SISTEM GUNLUKLERI (SYSLOG) LISTESI ---\n");
    while (suanki != NULL) {
        printf("[%d] %s", sayac++, suanki->logIcerigi);
        suanki = suanki->sonrakiNode;
    }
}

int main() {
    // Windows'ta test etmek için "syslog.txt" dosyasýný kullanýyoruz.
    // Önemli: Bu dosyanýn kodla ayný klasörde olmasý gerekir.
    const char* dosyaAdi = "syslog.txt";
    FILE* dosya = fopen(dosyaAdi, "r");

    if (dosya == NULL) {
        printf("Hata: '%s' dosyasi bulunamadi!\n", dosyaAdi);
        printf("Lutfen kodun yanina bir metin dosyasi olusturup adini %s yapin.\n", dosyaAdi);
        return 1;
    }

    LogDugumu* syslogListesi = NULL; // Listenin baþý (Head)
    char satirTamponu[1024];

    // Dosyayý satýr satýr oku ve Baðlý Liste yapýsýna aktar
    while (fgets(satirTamponu, sizeof(satirTamponu), dosya)) {
        logListesineEkle(&syslogListesi, satirTamponu);
    }

    fclose(dosya); // Dosya iþlemini bitir

    // Listeyi ekrana yazdýrarak doðrulama yap
    tumLoglariGoster(syslogListesi);

    // Bellek temizliði (Profesyonel bir kodda olmasý gereken adým)
    LogDugumu* silinecek;
    while (syslogListesi != NULL) {
        silinecek = syslogListesi;
        syslogListesi = syslogListesi->sonrakiNode;
        free(silinecek);
    }

    printf("\nIslem tamamlandi. Programdan cikiliyor...\n");
    return 0;
}
