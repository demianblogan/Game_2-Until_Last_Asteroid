[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game-Until_Last_Asteroid/blob/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game-Until_Last_Asteroid/blob/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game-Until_Last_Asteroid/blob/main/README.ua.md)

# Гра-Until_Last_Asteroid
Це моя перша гра для мого портфоліо. Її жанр "Shoot 'Em Up". В цій грі ви керуєте космічним кораблем і стріляєте по ворогам, таким я астероїди і інші кораблі. У вас є декілька життів, ви зробляєте бали і проходите рівні.

![1](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/3b0eb5bc-6564-49be-a4cb-a588289da779)

## **Кнопки керування:**<br />
Arrow up    -> Рухатися вперед<br />
Arrow left  -> Повернути вліво<br />
Arrow right -> Повернути парво<br />
Arrow down  -> Стрибнути в гіперпростір (стрибнути у випадкове місце)<br />
Space       -> Стріляти<br />
Escape      -> Закрити гру<br />

## **Как играть?**<br />
Коли ви запустите гру, ви побачите текст "Press any key to start". Це меню паузи. Щоразу, коли ви вмираєте - ви бачитимете це вікно. Якщо ви хочете закрити гру в будь-який час, просто натисніть клавішу Escape. У грі нескінченна кількість рівнів. Кожен рівень містить певну кількість астероїдів та кораблів. Щоб пройти рівень, ви повинні знищити їх усіх і почекати, поки не зникнуть усі ваші кулі. (Кожна куля зникає через 5 секунд). У грі є власний рахунок. Ви отримуєте бали за кожен знищений астероїд чи корабель. За кожні 1000 очок ви отримуєте додаткове життя. На початку гри у вас є 3 життя. Ви втрачаєте одне життя, коли вас торкається астероїд, ворожий корабель або його кулі. Якщо ви втратите всі свої життя - гра перезапуститься. Світ гри не має меж, тому якщо ви вилетіли за один бік світу – опинитеся на іншій його стороні.

## **Хто вороги?**<br />
Великий астероїд   - маленька швидкість, летить у випадковому напрямку. При знищенні розпадається на кілька середніх астероїдів і ви отримуєте +20 очок.<br />
Середній астероїд  - середня швидкість, летить у випадковому напрямку. При знищенні розпадається на кілька маленьких астероїдів і ви отримуєте +60 очок.<br />
Маленький астероїд - висока швидкість, летить у випадковому напрямку, при його знищенні ви отримуєте 100 очок.<br />
Маленький корабель - повільно повертається, рухається до вас, намагається доторкнутися до вас. При знищенні ви отримаєте +200 очок.<br />
Великий корабель   - повільно повертається, рухається до вас, стріляє у вас. При знищенні ви отримаєте +50 очок.<br />

## **Як створити і скомпілювати цей проект у Visual Studio?**<br />
ЗАМІТКА: у вас має бути встановлена Visual Studio 2022, яка підтримує стандарт C++20. Гугліть, як її встановити.<br />

1. Скачайте цей репозиторій як .zip файл і розархівуйте його.<br />
![2](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/97026464-e1ae-4787-820d-d5aeabf59556)

2. Створіть порожній C++ проект у Visual Studio.<br />
![3](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/ba48864e-86ff-421e-8f27-5be65d026eda)

3. Відкрийте папку проекту у провіднику та перемістіть усі файли з архіву туди.<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/a061ec73-8441-4bed-ab4b-b5b9e8afce44)

4. Щоб зробити всі ці файли видимими у вашому проекті, натисніть кнопку "Show all files" у Solution Explorer.<br />
![4](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/21533c25-f96e-4e53-bbb8-40ffdc63f1c3)

5. Виберіть усі файли в Solution Explorer, натисніть ПКМ і оберіть "Include In Project" (деякі файли у внутрішніх папках можуть не підключитися, тому ви можете підключити їх індивідуально).<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/e99f90ad-0c66-4e97-ba13-0b715ba0a52a)

6. Нам потрібно підключити бібліотеку SFML до проекту та змінити C++ стандарт на C++20. Тому йдіть у налаштування проекту.<br />
![5](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/bf9e841d-9119-49db-a0cf-107d75c39767)

7. Виберіть "All Configurations" та "All Platforms".<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/32a7b835-c44a-4807-88ef-f1aff00f1456)

8. У "Configuration Properties" перейдіть до вкладки "General", знайдіть "C++ Language Standard" і виберіть "ISO C++20 Standard (/std:c++20").<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/30d7c9f7-aefa-44aa-b352-f6d993872c4e)

9. Бібліотека SFML складається з 3 частин: .h/.cpp файли (папка include), .lib файли (папка lib) та .dll файли. Давайте підключимо спочатку папку "include". Перейдіть на вкладку "C/C++", знайдіть пункт "Additional Include Directories", натисніть на стрілочку праворуч і натисніть "<Edit...>".<br />
![8](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/79cb8d11-aabb-40e5-897f-ddbf3fe087c1)

10. У вікні, що з'явилося, двічі натисніть на порожній рядок і напишіть "$(ProjectDir)SFML\include", після чого натисніть кнопку "ОК" знизу вікна.<br />
![9](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/4257e884-5b7f-41da-b223-804560326285)

11. Вам потрібно зробити те саме з файлами .lib: перейдіть до вкладки "Linker", знайдіть пункт "Additional Library Directories", натисніть на стрілочку праворуч і натисніть "<Edit...>.<br />
![10](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/3ada0b06-2495-444c-ba47-03de46a538f5)

12. Зробіть те саме, що й у пункті №10, але тепер напишіть "$(ProjectDir)SFML\lib".<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/a0488d5d-414c-4050-9a61-9f9ae3860f52)

13. Майже готово. Нам тільки потрібно додати файли .dll в проект. Збережіть ваші зміни, натиснувши кнопку "Apply" знизу вікна налаштувань проекту, змініть конфігурацію на "Debug", перейдіть до вкладки "Linker" -> "Input", знайдіть пункт "Additional Dependencies", натисніть на стрілочку праворуч і натисніть "<Edit". ..>".<br />
![11](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/d6be1795-e5a9-49c4-b285-0bf18b07ed25)

14. У вікні, що з'явилося, напишіть наступні рядки:<br />
sfml-system-d.lib<br />
sfml-window-d.lib<br />
sfml-audio-d.lib<br />
sfml-graphics-d.lib<br />
sfml-network-d.lib<br />
та натисніть кнопку "Ok".<br />
![image](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/58e2669e-8805-4624-b2a5-aaf502f12297)

15. Натисніть "Apply", поміняйте конфігурацію на "Release" і зробіть те саме, тільки напишіть наступні рядки:<br />
sfml-system.lib<br />
sfml-window.lib<br />
sfml-audio.lib<br />
sfml-graphics.lib<br />
sfml-network.lib<br />
та натисніть кнопку "Ok".<br />
![12](https://github.com/demianblogan/Game-Until_Last_Asteroid/assets/105989117/3f3f6dd1-6dae-46f0-8f26-6a9c873685c7)

16. Ось і все! Натисніть Apply, і тепер бібліотека SFML підключена до вашого проекту.

17. Щоб скомпілювати та запустити гру, натисніть "Ctrl + F5".
