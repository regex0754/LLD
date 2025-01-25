#include <iostream>
#include <memory>
#include <cctype>
#include <cstring>

class TransportVehicle
{
  public:

  virtual ~TransportVehicle() {} // Without virtual, the destructor of the base class would be called, potentially leading to resource leaks or undefined behavior if the derived class has its own resources that need cleanup.

  virtual void transport() const = 0;
};

class Truck : public TransportVehicle
{
  public:

  void transport() const override 
  {
    std::cout << "Object transported using truck" << std::endl;
  }
};

class Ship : public TransportVehicle
{
  public:

  void transport() const override
  {
    std::cout << "Object transported using ship" << std::endl;
  }
};

class Logistics
{
  public:

  virtual ~Logistics() {} // Without virtual, the destructor of the base class would be called, potentially leading to resource leaks or undefined behavior if the derived class has its own resources that need cleanup.

  virtual std::shared_ptr<TransportVehicle> factoryMethod() const = 0;

  void transportGivenObject()
  {
    std::shared_ptr<TransportVehicle> transportVehicle = this->factoryMethod();
    transportVehicle->transport();
  }
};

class LandLogistics : public Logistics
{
  public:

  std::shared_ptr<TransportVehicle> factoryMethod() const override
  {
    return std::make_shared<Truck>();
  }
};

class WaterLogistics : public Logistics
{
  public:

  std::shared_ptr<TransportVehicle> factoryMethod() const override
  {
    return std::make_shared<Ship>();
  }
};


void toLowerCase(char* str)
{
  // change each character until we hit null terminator
  for (int i = 0; str[i] != '\0'; i++)
  {
    str[i] = std::tolower(static_cast<unsigned char>(str[i]));
  }
}

std::shared_ptr<Logistics> initialize(char* type)
{
  toLowerCase(type);

  std::shared_ptr<Logistics> logistics = nullptr;

  // switch case only works for int, long, enum, constexpr, etc. 
  if (strcmp(type, "land") == 0)
  {
    logistics = std::make_shared<LandLogistics>();
  }
  else if (strcmp(type, "water") == 0)
  {
    logistics = std::make_shared<WaterLogistics>();
  }
  else
  {
    throw std::runtime_error("invalid logistic type");
  }

  return logistics;
}

int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    try
    {
      std::shared_ptr<Logistics> logistics = initialize(argv[1]);
      logistics->transportGivenObject(); 
    }
    catch (const std::exception& ex)
    {
      std::cout << "Exception: " << ex.what() << std::endl;
    }
  }
  else
  {
    std::cout << "No arguments provided" << std::endl;
  }

  return 0;
}
