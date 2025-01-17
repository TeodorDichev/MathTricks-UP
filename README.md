# MathTricks-UP
Проектът е създаден за курса **"Увод в програмирането - практикум"** към **СУ "Св. Климент Охридски"**.
Проектът е игра, която се играе от двама играчи на правоъгълна _дъска_, започващи в противоположните краища на игралното поле. Размерите на дъската трябва да са между **[4, 4] и [12, 12]**. Правоъгълната дъска е запълнена с произволни операции **['+', '-', 'x', '/']** и стойности **[0-9]**, които модифицират точките на всеки играч. Дъската със сигурност съдържа операциите: 
  1) Поне една операция **събиране**;
  2) Поне една операция **изваждане**;
  3) Поне една клетка с **умножение по нула**;
  4) Поне една клетка с **умножение по две**;
  5) Поне една клетка с **деление на две**;
     
Играта дава еднакъв шанс на двамата играчи, като стойността на всяка клетка _расте съответно с размерите на матрицата_ и с _приближаването към центъра на матрицата_ изчислено чрез _евклидов метод за разстояние_. Всяка игра без победител, при преждевременно затваряне на програмата се запазва в .txt файл и може да бъде възстановена при рестартиране на играта. Всеки играч има различен цвят и може да се придвижва по всяка съседна клетка, включително и по диагоналите, което става чрез _въвеждане на координати_. Играта приключва, когато някой от играчите няма повече възможни ходове, като за да е честно ако вторият играч е на ход и той има възможност да играе трябва да довърши хода си.
