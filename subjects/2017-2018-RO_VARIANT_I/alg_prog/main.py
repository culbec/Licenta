from abc import ABC, abstractmethod

DEFAULT_VEHICLE_BASEPRICE: int = 100
DEFAULT_CAR_MODEL: str = "Ferrari"
DEFAULT_AUTOMATICCAR_ADDITIONALPRICE: int = 200
DEFAULT_CARWITHPARKINGSENSOR_SENSORTYPE: str = "FrontBack"

class Vehicle(ABC):
    def __init__(self, basePrice: int = DEFAULT_VEHICLE_BASEPRICE):
        self.basePrice = basePrice if basePrice > 0 else DEFAULT_VEHICLE_BASEPRICE
    
    @abstractmethod
    def description(self) -> str:
        pass

    def getPrice(self) -> int:
        return self.basePrice

class Car(Vehicle):
    def __init__(self, model: str = DEFAULT_CAR_MODEL, basePrice: int = DEFAULT_VEHICLE_BASEPRICE):
        Vehicle.__init__(self, basePrice)
        self.model = model if model else DEFAULT_CAR_MODEL
    
    def description(self) -> str:
        return self.model

class AutomaticCar(Car):
    def __init__(self, additionalPrice: int = DEFAULT_AUTOMATICCAR_ADDITIONALPRICE, model: str = DEFAULT_CAR_MODEL, basePrice: int = DEFAULT_VEHICLE_BASEPRICE):
        Car.__init__(self, model, basePrice)
        self.additionalPrice = additionalPrice if additionalPrice > 0 else DEFAULT_AUTOMATICCAR_ADDITIONALPRICE
    
    def description(self) -> str:
        return f"Automatic car {Car.description(self)}"
    
    def getPrice(self) -> str:
        return Car.getPrice(self) + self.additionalPrice
    
class CarWithParkingSensor(Car):
    def __init__(self, sensorType: str = DEFAULT_CARWITHPARKINGSENSOR_SENSORTYPE, model: str = DEFAULT_CAR_MODEL, basePrice: int = DEFAULT_VEHICLE_BASEPRICE):
        Car.__init__(self, model, basePrice)
        self.sensorType = sensorType if sensorType else DEFAULT_CARWITHPARKINGSENSOR_SENSORTYPE
    
    def description(self) -> str:
        return f"Car with parking sensor {self.sensorType} {Car.description(self)}"
    
    def getPrice(self) -> int:
        return Car.getPrice(self) + 2500

def modelWithNumberOfCars(vehicles: list[Vehicle]) -> list[tuple[str, int]]:
    result = {}
    
    for vehicle in vehicles:
        model = vehicle.description().split(" ")[-1]
        
        if model in result:
            result[model] += 1
        else:
            result[model] = 1
    
    return [(k, v) for k, v in result.items()]

def sortVehicles(vehicles: list[Vehicle]) -> None:
    n: int = len(vehicles)
    i = 0
    
    while i < n:
        if vehicles[i].getPrice() < 1000 or vehicles[i].getPrice() > 4000:
            v = vehicles[i]
            for j in range(i, len(vehicles) - 1):
                vehicles[j], vehicles[j+1] = vehicles[j+1], vehicles[j]
                        
            vehicles[len(vehicles) - 1] = v
            n -= 1
            i -= 1
        i += 1

def printDescriptions(vehicles: list[Vehicle]) -> None:
    for vehicle in vehicles:
        print(f"{vehicle.description()}: {vehicle.getPrice()}")
        
if __name__ == "__main__":
    vehicles: list[Vehicle] = [
        Car("Audi", 100),
        AutomaticCar(5000, "Audi", 15000),
        Car("Toyota", 10000),
        AutomaticCar(10000, "Mercedes", 80000),
        CarWithParkingSensor("Front", "Opel", 5000)
    ]
    
    pairs = modelWithNumberOfCars(vehicles)
    for (model, num) in pairs:
        print(f"{model}:{num}")
    
    sortVehicles(vehicles)
    printDescriptions(vehicles)