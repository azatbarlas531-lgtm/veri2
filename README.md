Linux Syslog Veri İşleme ve Bağlı Liste Uygulaması
​Bu proje, Veri Yapıları dersi ödevi kapsamında, Linux işletim sistemindeki sistem günlüklerinin (Syslog) dinamik bir veri yapısı olan Bağlı Liste (Linked List) kullanılarak yönetilmesini simüle etmek amacıyla geliştirilmiştir.
 Ödev Açıklaması
​Uygulama, /var/log/syslog yapısındaki verileri temsil eden bir metin dosyasını okur. Okunan her bir log satırı, bellekte dinamik olarak oluşturulan bir düğüme (node) aktarılır ve bu düğümler birbirine bağlanarak bir liste oluşturur.
​ Teknik Detaylar ve Seçimler
​1. Neden Bağlı Liste (Linked List) Seçildi?
​Syslog verileri akışkan ve miktarı önceden kestirilemeyen verilerdir.
• ​Dinamik Bellek Yönetimi: Sabit boyutlu diziler (Array) kullanıldığında bellek israfı veya yetersiz alan sorunu yaşanabilir. Bağlı liste ise sadece ihtiyaç duyulan her bir log satırı için bellekte yer ayırır (malloc).
• ​Esneklik: Veri eklendikçe liste dinamik olarak büyür, bu da sistem kaynaklarının verimli kullanılmasını sağlar.
​2. Kullanılan Veri Yapısı Türü
​Projede Tek Yönlü Bağlı Liste (Singly Linked List) kullanılmıştır. Log verileri genellikle kronolojik sırada işlendiği ve tek yönlü bir okuma yeterli olduğu için bu yapı en verimli çözümdür.
​3. Fonksiyonel Bileşenler
• ​struct LogDugumu: Veri (log metni) ve bir sonraki düğümün adresini tutan işaretçiyi barındırır.
• ​logListesineEkle: Yeni logları listenin sonuna ekleyerek sıralamayı korur.
• ​free Operasyonu: Bellek sızıntılarını (Memory Leak) önlemek için program sonunda tüm düğümler temizlenir.
​ Nasıl Çalıştırılır?
• ​veri2.c ve syslog.txt dosyalarını aynı dizine indirin.
• ​C derleyiciniz (GCC, Dev-C++ vb.) ile main.c dosyasını derleyin.
• ​Uygulamayı çalıştırdığınızda, syslog.txt içeriği bağlı listeye aktarılacak ve ekranda listelenecektir.
