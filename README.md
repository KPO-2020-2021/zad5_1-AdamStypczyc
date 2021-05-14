## Podsumowanie mojej pracy
Aby wykonać to zadanie musiałem przede wszystkim do dołączonego zalążka dodać klasę prostokąt, wykonać testy, umożliwić obrót, poprzez zaimplementowanie macierzy obrotu oraz połączyć to wszystko w całość. Prostokąt konstruuję poprzez podanie jednego punktu (w mojej głowie wyobrażałem sobie ten punkt jako lewy dolny róg) oraz  wysokości i szerokości prostokąta. W ten sposób określane są pozostałe punkty i nie trzeba sprawdzać czy punkty podane przez użytkownika rzeczywiście tworzą prostokąt. Niestety nie można utworzyć prostokąta, którego boki nie są równoległe do osi XY, do momentu obrócenia go. Wielokrotny obrót myślę, że nieco udoskonaliłem, ponieważ nie wykonuję tego oborotu poprzez pętlę, lecz poprzez obliczenie kąta o jaki ostatecznie obróci się prostokąt. Wyszedłem z założenie, że po co np. obracać prostokąt o 90 stopni 37 razy jak można obrócić go 1 raz. Przyśpiesza to znacząco działanie programu przy dużej ilości obrotów i chociaż w jakimś stopniu niweluje błąd wynikający z typu double. Przy testowaniu używam pętli for i widać, że po dużej ilości obrotu boki zaczynają się rozjeżdżać. Początkowo nie pokazywało błędu, co mnie dziwiło. Było to spowodowane podobnym błędem jaki mieliśmy na zajęciach. Bez std:: przed abs nie czytało poprawnie wartości bezwzględnej. Menu użytkownika zostało udoskonalone tak, że przy wpisywaniu liczb, które liczbami nie są (np. znak a) dostajemy komunikat o błędzie. Jako modyfikację musiałem wykonać metodę obliczającą wyznacznik macierzy metodą eliminacji Gaussa. 
## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Requirements: 

Example:

``` bash
> mkdir build && cd build
> cmake .. # options: -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release], Debug is default
> make
> ./main
> make test      # Makes and runs the tests.
> make coverage  # Generate a coverage report.
> make doc       # Generate html documentation.
```


