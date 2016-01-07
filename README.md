# CSE_395_Project_I_2015
2015-2016 Fall Project I Source Codes

Kullanım Klavuzu

Küpümüzü kullanmak için aşağıdaki yolları izliyoruz.

Öncelikle küpü bir kablosuz ağa bağlayıp ardından SSH ile küpe bağlanıyoruz. 
Küpe bağlanmak için gerekli olan kullanıcı adı:pi ve parola:raspberry
SSH bağlantısından başka hdmi girişi olan herhangi bir ekrana bağlayarak da küp ile ilgili işlemlere devam edebiliriz. 
Ancak biz tüm işlemlerimizi SSH bağlantısı üzerinden gerçekleştirdik. Anlatımımız da ona göre devam edecek. 

Modüllerin çalışma sırası server-küp-arayüz şeklinde. Küp ve arayüzün bağlanabilmesi için server çalışmaya başlamak durumunda.
Server ı çalıştırmak için iç mekan ve dış mekan olarak ayrı klasörlerde bulunan kodları çalıştırmamız lazım. 
İç mekan için anlatamı yapacağım dış mekanda oluşabilecek farklılıkları da ayrıca belirteceğim. 
İç mekan klasöründeki kaynak kodları derledikten sonra "./server portno" şeklinde çalıştırıyoruz. 
Burada port numarası istenilen numara seçilebilir ancak küpü ve arayüzü de aynı numarayla çalıştırmak önemli. 
Bu şekilde çalıştırdıktan sonra "waiting for clients" yazısıyla birlikte server bağlanacak aygıtları beklemeye başlıyor.



Sonrasında küpte de, iç mekan klasöründeki kodları çalıştırıp, aynı ip ve port numarası ile 
"./indoor ip portno" şeklinde çalıştırıyoruz. Bağlantının ardından terminalde "cube module has connected" yazısı 
belirince küpümüzün de bağlı olduğunu anlıyoruz. 
 
İç mekanda konum bumak için wi fi hotspotlarını kullanıyoruz. 
Bu sebeple içeride konum alabilmek için ssid'si 1'den 11'e kadar numaralandırılmış 11 tane wi fi vericisine ihtiyacımız olacak.
Sonrasında varış konuma gelene kadar her nokta değişiminde küp bu noktayı server'a, server da arayüze gönderiyor.
Varış konumuna varıldığından programlar sonlanıyor.
 
Dış mekanda iç mekanla çalışma şekli olarak aynı. Sadece çalıştırılan kodlar farklı. 
Indoor Cube klasörü değil de Outdoor Cube klasörü içinden devam edilmeli. 
Dış mekanda başlangıçta konum almak çok uzun sürebiliyor, bunun için de başlangıç konumunu elle vermek testin hızlanmasına 
fayda sağlayacaktır.
 
 
 
Notlar
1.  Arayüz kodunun en son halinde ip numarası olarak localhost(127.0.0.1) yazıldı. 
    Eğer farklı bir ip ile deneme yapılmak istenirse bunlar da değiştirilmeli. 
    Kod satırları workerthread.h 47. satır, dialogthread.h 50. satırlar. 
 
2.  İç mekan için default port 4664, dış mekan için ise 4665 olarak belirlenmiştir. 
    Bunlar da kaynak kodda ip numarasının yanında girilmiştir.
 
3.  Interface kodlarında path sorunu olmaması için Qt Creator da debug modda shadow build yapılmalı.
 
