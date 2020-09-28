# Conway-s-Game
2.Разработка, алгоритмы

Игра «Жизнь» (Conway's Game of Life) -клеточный автомат, придуманный математиком Джоном Конвеемв 1970 году. Реализация данного автомата похожа на развитие популяции примитивных организмов.Закономерности “игры”отражаются во многих теориях из самых разных областей науки: от квантовой физики и бактериологии до кибернетики и астрономии.
Правила

• Место действия игры -клеточное поле. Его размер тыможешьуказать самили сделать бесконечным/зацикленным• Поколение -это одна итерация изменения поля• Каждая клетка может иметь два состояния: заполнена(жива), пуста(мертва)

• У каждой клетки есть соседи -8 соседних клеток

• В пустойклетке, рядом с которой ровно три заполненныеклетки, зарождается жизнь

• Если у заполненнойклетки три или два заполненныхсоседа, то она продолжает быть заполненной

• В противном случае, если соседей меньше двух или больше трёх, клетка умирает («от одиночества» или «от перенаселённости»).



Игра реализована на консоли. Для начала необходимо ввести координаты клеток на поле от 1 до 15, после каждого ввода приложение будет предлагать ввести еще одну или начать игру. После начала введите 'n' для перехода к следующему поколение, либо 'r' для перезапуска игр, либо 'e' для выхода из игры.
