import java.util.ArrayList;
import java.util.List;

class HelperClass{      //Вспомогательный класс
	private HelperClass() throws Exception {
		throw new Exception("Ошибка: Класс не должен иметь экземпляров.");
	}
	public static int IntegerValidation(int value) {    //Метод для корректировки значений int в случае ошибки
		if(value < 0) {
			return 0;
		}else {
			return value;
		}
	}
}

class Load {        //Груз
    private String contentName;    //Наименование содержимого
    private int weight;            //Вес содержимого

    public Load(String contentName, int weight) {    //Инициализация груза (конструктор)
    	this.contentName = contentName;
    	this.weight = weight;
    }

    public Load() {
        contentName = "none";
        weight = 0;
    }

    public int GetWeight() {
        return weight;
    }

    public void Output() {    //Вывод инф. о грузе
        System.out.printf("Тип содержимого: %s\n", contentName);
        System.out.printf("Вес содержимого (в одном к-ре): %d\n", weight);
    }
}

class Container {    //Контейнер
    private String destinationAddress;    //Адрес назначения
    private String IDNumber;              //Идентификационный номер
    private Load load;                    //Груз в контейнере

    public Container(String destinationAddress, String IDNumber, Load load) {    //Инициализация контейнера (конструктор)
        this.destinationAddress = destinationAddress;
        this.IDNumber = IDNumber;
        this.load = load;
    }

    public Container() {
        destinationAddress = "none";
        IDNumber = "none";
    }

    public Load GetLoad() {
        return load;
    }

    public void CorrectContainerID(String newIDNumber) {    //Скорректировать ID контейнера
        IDNumber = newIDNumber;
    }

    public void Output() {    //Вывод инф. о контейнере
        System.out.printf("Адрес назначения: %s\n", destinationAddress);
        System.out.printf("Идентификационный номер к-ра: %s\n", IDNumber);
        load.Output();
    }
}

class Team {     //Команда
    private int numberOfPeople;           //Кол-во членов команды
    private String foremanName;           //Имя бригадира

    public Team(int numberOfPeople, String foremanName) {    //Инициализация команды (конструктор)
    	this.numberOfPeople = numberOfPeople;
    	this.foremanName = foremanName;
    }

    public Team() {
        numberOfPeople = 0;
        foremanName = "none";
    }

    public int GetNumberOfPeople() {
        return numberOfPeople;
    }

    public void Output() {    //Вывод инф. о команде
        System.out.printf("Кол-во членов команды: %d\n", numberOfPeople);
        System.out.printf("Имя бригадира: %s\n", foremanName);
    }
}

class Captain {     //Капитан
    private String name;             //Имя
    private String licenseNumber;    //№ лицензии
    private Team team;               //Команда капитана

    public Captain(String name, String licenseNumber, Team team) {    //Инициализация капитана (конструктор)
    	this.name = name;
    	this.licenseNumber = licenseNumber;
    	this.team = team;
    }

    public Captain() {
        name = "none";
        licenseNumber = "none";
    }

    public Team GetTeam() {
        return team;
    }

    public String GetLicense() {
        return licenseNumber;
    }

    public void Output() {    //Вывод инф. о капитане
        System.out.printf("Имя капитана: %s\n", name);
        System.out.printf("№ лицензии капитана: %s\n", licenseNumber);
        team.Output();
    }
}

class CaptainDatabase {       //База доступных капитанов (вспомог. класс)
    private List<Captain> Database;
    private int arrayCounter;

    public CaptainDatabase() {
        Database = new ArrayList<>();
        arrayCounter = 0;
    }

    public void AddEntry(Captain newCaptain) {
        Database.add(newCaptain);
        arrayCounter++;
    }

    public Captain GetCaptain(String licenseNumber) {
        for (int i = 0; i < arrayCounter; i++) {
            if (Database.get(i).GetLicense().equals(licenseNumber)) {
                return Database.get(i);
            }
        }
        return null;
    }
}

class Ship {               //Корабль
    private Container container;         //Тип контейнеров, которые перевозит корабль
    private int numberOfContainers;      //Кол-во контейнеров на корабле
    private Captain captain;             //Капитан корабля
    private boolean condition;           //Состояние корабля (приемлемое/нет)
    private static int shipsTotal = 0;   //Всего кораблей [static]

    public Ship(Container container, int numberOfContainers, String assignedCaptainLicense, boolean condition, CaptainDatabase Database1) {    //Инициализация корабля (конструктор)
    	try {
    	    if (numberOfContainers < 0) {
    	        throw new Exception();
    	    }
    	} catch (Exception e) {
    	    System.out.println("Ошибка: Число контейнеров не должно быть меньше нуля.");
    	}
    	
    	this.container = container;
    	this.numberOfContainers = numberOfContainers;
    	this.captain = Database1.GetCaptain(assignedCaptainLicense);
        this.condition = condition;
        shipsTotal++;
    }

    public Ship() {
        numberOfContainers = 0;
        condition = false;
        captain = null;
        shipsTotal++;
    }
    
    public void AddLoad(int additionalLoad) {    //Добавить груз
        numberOfContainers += additionalLoad;
    }

    public void ChangeShipContainers(Container newContainer, int newNumberOfContainers) {    //Перезагрузить корабль (другими контейнерами)
        container = newContainer;
        numberOfContainers = newNumberOfContainers;
    }
    
    public void ChangeShipContainers(int newNumberOfContainers) {                            //Перезагрузить корабль (только кол-во)
        numberOfContainers = newNumberOfContainers;
    }

    public boolean CheckViolations() {     //Проверить нарушения
        if (!condition || captain.GetTeam().GetNumberOfPeople() > 20 || (numberOfContainers * container.GetLoad().GetWeight() > 500)) {
            return true;
        } else {
            return false;
        }
    }

    public int CalcFee() {       //Рассчитать плату за проход
        int fine = 0;
        if (CheckViolations()) {
            fine = 5000;
        }
        return (HelperClass.IntegerValidation(numberOfContainers * container.GetLoad().GetWeight() + fine));
    }

    public void Output() {             //Вывод всей инф. о корабле
        container.Output();
        System.out.printf("Кол-во контейнеров: %d\n", numberOfContainers);
        captain.Output();
        if (condition) {
            System.out.println("Состояние приемлимое.");
        } else {
            System.out.println("Состояние неприемлимое.");
        }
    }
    
    public static void OutTotalShips() {      //Вывод shipsTotal
    	System.out.printf("Всего кораблей: %d\n", shipsTotal);
    }
}



public class HelloWorld {
	public static void main(String[] args) {
        CaptainDatabase globalDatabase1 = new CaptainDatabase();
        
        Load fish = new Load("Fish", 50);
        Load furniture = new Load("Furniture", 100);
        Container contOne = new Container("-15 20 150", "1234567", fish);
        Container contTwo = new Container("-150 70 -10", "7654321", furniture);
        Team teamOne = new Team(10, "Joe");
        Team teamTwo = new Team(5, "Mark");
        Captain captainOne = new Captain("Josh", "1234567", teamOne);
        Captain captainTwo = new Captain("Jon", "7654321", teamTwo);
        globalDatabase1.AddEntry(captainOne);
        globalDatabase1.AddEntry(captainTwo);
        
        Ship.OutTotalShips();
        
        Ship shipOne = new Ship(contOne, 10, "1234567", true, globalDatabase1);
        
        Ship.OutTotalShips();
        
        System.out.printf("Плата за проход 1: %d\n", shipOne.CalcFee());
        
        shipOne.ChangeShipContainers(contTwo, 20);
        System.out.printf("Плата за проход 2: %d\n", shipOne.CalcFee());
        
        shipOne.AddLoad(10);
        System.out.printf("Плата за проход 3: %d\n", shipOne.CalcFee());
        
        Ship shipTwo = new Ship(contTwo, 10, "7654321", false, globalDatabase1);
        System.out.printf("Плата за проход 4: %d\n\n", shipTwo.CalcFee());
        
        shipTwo.Output();
        
        Ship[] shipArray = new Ship[]{new Ship(contOne, 10, "1234567", true, globalDatabase1), shipTwo, new Ship(contOne, 20, "1234567", true, globalDatabase1)};
        System.out.printf("\nПлата за проход 5: %d\n\n", shipArray[2].CalcFee());
        
        shipArray[0].Output();
        
        Ship.OutTotalShips();
        
        Ship shipThree = new Ship(contOne, -10, "1234567", true, globalDatabase1);
        
        Ship[][] shipArrayDouble = {
                {shipOne, new Ship(contOne, 20, "1234567", true, globalDatabase1)},
                {new Ship(contTwo, -19, "7654321", true, globalDatabase1), shipThree}
        };

        shipArrayDouble[0][1].AddLoad(19);
        shipArrayDouble[0][1].Output();
        
        System.out.println("Завершение работы.");
    }
}
