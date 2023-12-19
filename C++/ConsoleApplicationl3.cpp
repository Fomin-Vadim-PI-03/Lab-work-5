#include <iostream>
#include <string>


class Load {        //Груз
private:
    std::string contentName;    //Наименование содержимого
    int weight;                 //Вес содержимого

public:
    Load(std::string ContentName, int Weight);    //Инициализация груза (конструктор)
    Load();
    int GetWeight();
    std::string GetContent();
    void Output();    //Вывод инф. о грузе
  
};

Load::Load(std::string ContentName, int Weight) {
    this->contentName = ContentName;
    this->weight = Weight;
}
Load::Load() {
    contentName = "none";
    weight = 0;
}
int Load::GetWeight() {
    return weight;
}
std::string Load::GetContent() {
    return contentName;
}
void Load::Output() {
    printf("Тип содержимого: %s\n", contentName.c_str());
    printf("Вес содержимого (в одном к-ре): %d\n", weight);
}



class Container {    //Контейнер
private:
    std::string destinationAddress;    //Адрес назначения
    std::string IDNumber;              //Идентификационный номер
    Load load;                         //Груз в контейнере

public:
    Container(std::string DestinationAddress, std::string IDNumber, Load Load);    //Инициализация контейнера (конструктор)
    Container();
    Load GetLoad();
    void correctContainerID(std::string B);    //Скорректировать ID контейнера
    void Output();    //Вывод инф. о контейнере
    
};

Container::Container(std::string DestinationAddress, std::string IDNumber, Load Load) {
    this->destinationAddress = DestinationAddress;
    this->IDNumber = IDNumber;
    this->load = Load;
}
Container::Container() {
    destinationAddress = "none";
    IDNumber = "none";
}
Load Container::GetLoad() {
    return load;
}
void Container::correctContainerID(std::string newIDNumber) {
    IDNumber = newIDNumber;
}
void Container::Output() {
    printf("Адрес назначения: %s\n", destinationAddress.c_str());
    printf("Идентификационный номер к-ра: %s\n", IDNumber.c_str());
    load.Output();
}



class Team{     //Команда
private:
    int numberOfPeople;           //Кол-во членов команды
    std::string foremanName;      //Имя бригадира

public:
    Team(int NumberOfPeople, std::string ForemanName);    //Инициализация команды (конструктор)
    Team();
    int GetNumberOfPeople();
    void Output();    //Вывод инф. о команде
};

Team::Team(int NumberOfPeople, std::string ForemanName) {
    this->numberOfPeople = NumberOfPeople;
    this->foremanName = ForemanName;
}
Team::Team() {
    numberOfPeople = 0;
    foremanName = "none";
}
int Team::GetNumberOfPeople() {
    return numberOfPeople;
}
void Team::Output() {
    printf("Кол-во членов команды: %d\n", numberOfPeople);
    printf("Имя бригадира: %s\n", foremanName.c_str());
}



class Captain{     //Капитан
private:
    std::string name;             //Имя
    std::string licenseNumber;    //№ лицензии
    Team team;                    //Команда капитана

public:
    Captain(std::string Name, std::string LicenseNumber, Team Team);    //Инициализация капитана (конструктор)
    Captain();
    Team GetTeam();
    std::string GetLicense();
    void Output();    //Вывод инф. о капитане
};

Captain::Captain(std::string Name, std::string LicenseNumber, Team Team) {
    this->name = Name;
    this->licenseNumber = LicenseNumber;
    this->team = Team;
}
Captain::Captain() {
    name = "none";
    licenseNumber = "none";
}
Team Captain::GetTeam() {
    return team;
}
std::string Captain::GetLicense() {
    return licenseNumber;
}
void Captain::Output() {
    printf("Имя капитана: %s\n", name.c_str());
    printf("№ лицензии капитана: %s\n", licenseNumber.c_str());
    team.Output();
}



class CaptainDatabase {   //База доступных капитанов (вспомог. класс)
private:
    Captain* Database[5];
    int arrayCounter;

public:
    CaptainDatabase() {
        arrayCounter = 0;
        *Database = {};
    }

    void AddEntry(Captain &newCaptain) {
        if (arrayCounter < 5) {
            Database[arrayCounter] = &newCaptain;
            arrayCounter++;
        }
    }

    Captain* GetCaptain(std::string licenseNumber) {
        for (int i = 0; i < arrayCounter; i++) {
            if (Database[i]->GetLicense() == licenseNumber) {
                return Database[i];
            }
        }
        return nullptr;
    }

}Database1;    //Объявление базы данных капитанов



class Ship {               //Корабль
private:
    Container container;       //Тип контейнеров, которые перевозит корабль
    int numberOfContainers;    //Кол-во контейнеров на корабле
    Captain* captain;          //Капитан корабля
    bool condition;            //Состояние корабля (приемлемое/нет)
    static int shipsTotal;     //Всего кораблей [static]

public:
    Ship(Container Container, int NumberOfContainers, std::string AssignedCaptainLicense, bool Condition);    //Инициализация корабля (конструктор)
    Ship();
    ~Ship();
    void AddLoad(int additionalLoad);    //Добавить груз
    void ChangeShipContainers(Container newContainer, int newNumberOfContainers);    //Перезагрузить корабль (другими контейнерами)
    void ChangeShipContainers(int newNumberOfContainers);                            //Перезагрузить корабль (только кол-во)
    void Output();                       //Вывод всей инф. о корабле

    static void OutTotalShips();      //Вывод shipsTotal

    friend int CalcFee(Ship& currShip);
    friend bool CheckViolations(Ship& currShip);

    Ship operator + (Ship Ship2)      //Перегрузка оператора '+'
    {
        if (this->container.GetLoad().GetContent() == Ship2.container.GetLoad().GetContent()) {
            return Ship(Ship2.container, (this->numberOfContainers + Ship2.numberOfContainers), Ship2.captain->GetLicense(), Ship2.condition);
        }
    }

    Ship& operator++ ()         //Перегрузка инкремента (префиксный)
    {
        numberOfContainers += 1;
        return *this;
    }

    Ship operator++ (int)       //Перегрузка инкремента (постфиксный)
    {
        Ship copy = *this;
        ++(*this);
        return copy;
    }

};

int Ship::shipsTotal = 0;      //Инициализация static переменной
void Ship::OutTotalShips() {   //Инициализация static метода
    printf("Всего кораблей: %d\n", shipsTotal);
}

Ship::Ship(Container Container, int NumberOfContainers, std::string AssignedCaptainLicense, bool Condition) {
    try {
        if (NumberOfContainers < 0) {
            throw 1;
        }
    }
    catch (...) {
        printf("Ошибка: Число контейнеров не должно быть меньше нуля.\n");
    }

    this->container = Container;
    this->numberOfContainers = NumberOfContainers;
    this->captain = Database1.GetCaptain(AssignedCaptainLicense);
    this->condition = Condition;
    shipsTotal++;
}
Ship::Ship() {
    numberOfContainers = 0;
    condition = false;
    captain = nullptr;
    shipsTotal++;
}
Ship::~Ship() {
    shipsTotal--;
}
void Ship::AddLoad(int additionalLoad) {
    numberOfContainers += additionalLoad;
}
void Ship::ChangeShipContainers(Container newContainer, int newNumberOfContainers) {
    container = newContainer;
    numberOfContainers = newNumberOfContainers;
}
void Ship::ChangeShipContainers(int newNumberOfContainers) {
    numberOfContainers = newNumberOfContainers;
}
void Ship::Output() {
    container.Output();
    printf("Кол-во контейнеров: %d\n", numberOfContainers);
    captain->Output();
    if (condition) {
        printf("Состояние приемлимое.\n");
    }
    else {
        printf("Состояние неприемлимое.\n");
    }
}


bool CheckViolations(Ship& currShip) {     //Проверить нарушения
    if (!currShip.condition || currShip.captain->GetTeam().GetNumberOfPeople() > 20 || (currShip.numberOfContainers * currShip.container.GetLoad().GetWeight() > 500)) {
        return true;
    }
    else {
        return false;
    }
}
int CalcFee(Ship& currShip) {     //Рассчитать плату за проход
    int fine = 0;
    if (CheckViolations(currShip)) {
        fine = 5000;
    }

    return (currShip.numberOfContainers * currShip.container.GetLoad().GetWeight() + fine);
}


int main()
{
    setlocale(0, "");

    Load fish("Fish", 50);
    Load furniture("Furniture", 100);
    Container contOne("-15 20 150", "1234567", fish);
    Container contTwo("-150 70 -10", "7654321", furniture);
    Team teamOne(10, "Joe");
    Team teamTwo(5, "Mark");
    Captain captainOne("Josh", "1234567", teamOne);
    Captain captainTwo("Jon", "7654321", teamTwo);

    Database1.AddEntry(captainOne);
    Database1.AddEntry(captainTwo);

    Ship shipOne(contOne, 10, "1234567", true);

    shipOne.OutTotalShips();

    printf("Плата за проход 1: %d\n", CalcFee(shipOne));

    shipOne.ChangeShipContainers(contTwo, 20);

    printf("Плата за проход 2: %d\n", CalcFee(shipOne));

    shipOne.AddLoad(10);

    printf("Плата за проход 3: %d\n", CalcFee(shipOne));

    Ship* shipTwo = new Ship (contTwo, 10, "7654321", false);

    shipOne.OutTotalShips();

    printf("Плата за проход 4: %d\n\n", CalcFee(*shipTwo));

    (*shipTwo).Output();

    printf("\nРабота с динамическим массивом объектов: \n");    ///
    Ship* shipArray = new Ship[3]{{contOne, 10, "1234567", true}, {contTwo, 15, "7654321", true}, {contOne, 20, "1234567", true}};

    printf("Плата за проход 5: %d\n\n", CalcFee(shipArray[2]));

    shipArray[0].Output();

    delete[] shipArray;

    printf("\nРабота с массивом динамических объектов: \n");    ///

    Ship** shipArray2 = new Ship* [2] {&shipOne, shipTwo};

    shipArray2[0]->AddLoad(10);

    printf("Плата за проход 6: %d\n\n", CalcFee(*shipArray2[0]));

    Ship shipThree(contTwo, 15, "1234567", true);

    shipThree = shipOne + shipOne;
    shipThree.Output();

    shipOne++;
    ++shipOne;

    shipOne.Output();

    Ship shipFour(contOne, -10, "1234567", true);

    Ship shipArrayDouble[2][2] = { {shipOne, {contOne, 20, "1234567", true}}, {{contTwo, -19, "7654321", true}, shipThree }};  //Работа с двойным массивом

    shipArrayDouble[1][0].AddLoad(19);

    delete[] shipArray2;
    delete shipTwo;

    return 0;
}
