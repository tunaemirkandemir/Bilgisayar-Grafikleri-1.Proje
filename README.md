### Sokak Sahnesi - OpenGL Projesi
Bu proje, OpenGL kullanarak bir sokak sahnesi oluşturmayı amaçlamaktadır. Sahne, sokak lambaları, kaldırımlar, yol ve binalar gibi çeşitli öğeleri içermektedir. Kamera hareketleri, kullanıcı etkileşimi ile sağlanır ve sahne, birinci şahıs bakış açısıyla görüntülenebilir.

## Hikaye
Küçük, kırmızı çatılı evin penceresinden sıcak bir ışık sızıyordu. Bahçedeki ağaçların dalları hafifçe sallanıyordu. Gökyüzü, lacivert bir örtü gibiydi ve üzerinde tek tük parlayan yıldızlar vardı. Tam o sırada, evin tam üstünden parlak bir ışık çizgisi kaydı. Kayan bir yıldız, kısa bir an için her şeyi aydınlattı. Penceredeki ışıkta bir anlık bir parıltı oldu, sonra yıldız karanlığa karıştı. Ev sessizce orada kaldı, gökyüzü de öyle. O kısacık an, geceye sihirli bir dokunuş katmıştı sadece.

## Özellikler
Çoklu Sokak Lambaları: Sahneye birkaç sokak lambası eklenmiştir. Bu lambalar, aydınlatma efektleri ile sahnenin görsel kalitesini artırır.

Binalar ve Yollar: Sokak boyunca binalar ve yollar yer alır. Binalar, çeşitli geometrik şekillerle modellenmiştir.

Dinamik Kamera Hareketi: Kullanıcı klavye ok tuşları ile kamera hareketini kontrol edebilir. Kamera hareketleri, FPS (Birinci Şahıs Görünümü) tarzında tasarlanmıştır.

Farklı Işıklar: Sahneye eklenen ışıklar, Phong aydınlatma modeli ile sahnenin daha gerçekçi görünmesini sağlar.

## Gereksinimler
GLFW: Pencere yönetimi ve kullanıcı etkileşimi için.

GLAD: OpenGL işlevlerini yüklemek için.

GLM: Vektör ve matris hesaplamaları için.

OpenGL 3.3 veya üstü: Görselleştirme ve render işlemleri için.

## Başlangıç
Bu projeyi çalıştırmak için aşağıdaki adımları takip edebilirsiniz:

# 1. Bağımlılıkları Yükleyin
GLFW, GLAD ve GLM kütüphanelerini yüklemeniz gerekmektedir. Bunları aşağıdaki bağlantılardan veya paket yöneticileri aracılığıyla kurabilirsiniz:

GLFW İndir

GLAD İndir

GLM İndir

# 2. Projeyi İndirin
Projeyi GitHub veya benzeri bir kaynaktan indirin.

# 3. Derleme
Projeyi derlemek için CMake veya başka bir derleyici kullanabilirsiniz. Aşağıdaki adımları izleyerek projeyi derleyebilirsiniz:

bash
Kopyala
Düzenle
mkdir build
cd build
cmake ..
make
# 4. Çalıştırma
Projeyi başarıyla derledikten sonra aşağıdaki komutu kullanarak çalıştırabilirsiniz:

bash
Kopyala
Düzenle
./StreetScene
## Kullanıcı Etkileşimi
W/S: Kamera ileri/geri hareketi.

A/D: Kamera sola/sağa hareketi.

Fare: Kamera yönünü değiştirmek.

ESC: Uygulamayı kapatmak.

## Görsel
Projede sokak lambaları, binalar ve yol geometrilerini içeren bir sokak sahnesi bulunmaktadır. Her sokak lambası, farklı pozisyonlarda yer alır ve sahneye uygun aydınlatma ekler.

## Geliştirme
Proje üzerinde geliştirme yapmak için, yeni ışık kaynakları ekleyebilir, sahneye yeni binalar veya farklı geometrik şekiller ekleyebilirsiniz. Ayrıca kamera kontrolünü daha verimli hale getirebilirsiniz.
