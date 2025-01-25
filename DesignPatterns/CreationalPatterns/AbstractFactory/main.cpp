#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstring>
#include <cctype>

class AbstractFurniture
{
    public:
    virtual ~AbstractFurniture() {};
    virtual void whatAmI() const = 0;

    void defaultWhatAmI() const
    {
        std::cout << "A Furniture" << std::endl;
    }
};

// Family1 type classified products

class AbstractTable : public AbstractFurniture
{
    public:
    virtual ~AbstractTable() {};

    void whatAmI() const override
    {
        std::cout << "A Table" << std::endl;
    }
};

class AbstractChair : public AbstractFurniture
{
    public:
    virtual ~AbstractChair() {};

    void whatAmI() const override
    {
        std::cout << "A Chair" << std::endl;
    }
};

class AbstractSofa : public AbstractFurniture
{
    public:
    virtual ~AbstractSofa() {};

    void whatAmI() const override
    {
        std::cout << "A Sofa" << std::endl;
    }
};

// Family1 * Family2 types of classified products

// All Table products
class TableVictorianStyle : public AbstractTable
{
    public:

    void whatAmI() const override
    {
        std::cout << "A Victorian Style Table" << std::endl;
    } 
};

class TableModernStyle : public AbstractTable
{
    public:
    void whatAmI() const override
    {
        std::cout << "A Modern Style Table" << std::endl;
    }
};

class TableArtDecoStyle : public AbstractTable
{
    public:
    void whatAmI() const override
    {
        std::cout << "An ArtDeco Style Table" << std::endl;
    }
};

// All Chair products
class ChairVictorianStyle : public AbstractChair
{
    public:

    void whatAmI() const override
    {
        std::cout << "A Victorian Style Chair" << std::endl;
    } 
};

class ChairModernStyle : public AbstractChair
{
    public:
    void whatAmI() const override
    {
        std::cout << "A Modern Style Chair" << std::endl;
    }
};

class ChairArtDecoStyle : public AbstractChair
{
    public:
    void whatAmI() const override
    {
        std::cout << "An ArtDeco Style Chair" << std::endl;
    }
};

// All Sofa products
class SofaVictorianStyle : public AbstractSofa
{
    public:

    void whatAmI() const override
    {
        std::cout << "A Victorian Style Sofa" << std::endl;
    } 
};

class SofaModernStyle : public AbstractSofa
{
    public:
    void whatAmI() const override
    {
        std::cout << "A Modern Style Sofa" << std::endl;
    }
};

class SofaArtDecoStyle : public AbstractSofa
{
    public:
    void whatAmI() const override
    {
        std::cout << "An ArtDeco Style Sofa" << std::endl;
    }
};

// Abstract factory with factory methods to create family1 type objects
class AbstractFurnitureFactory
{
    public:
    virtual ~AbstractFurnitureFactory() {};

    virtual std::shared_ptr<AbstractTable> createTable() const = 0;
    virtual std::shared_ptr<AbstractChair> createChair() const = 0;
    virtual std::shared_ptr<AbstractSofa> createSofa() const = 0;
};

// concrete factories for the last level of family (family2) with methods for family1 type
class ConcreteFurnitureFactoryVictorianStyle : public AbstractFurnitureFactory
{
    std::shared_ptr<AbstractTable> createTable() const override
    {
        return std::make_shared<TableVictorianStyle>();
    }

    std::shared_ptr<AbstractChair> createChair() const override
    {
        return std::make_shared<ChairVictorianStyle>();
    }

    std::shared_ptr<AbstractSofa> createSofa() const override
    {
        return std::make_shared<SofaVictorianStyle>();
    }
};

class ConcreteFurnitureFactoryModernStyle : public AbstractFurnitureFactory
{
    std::shared_ptr<AbstractTable> createTable() const override
    {
        return std::make_shared<TableModernStyle>();
    }

    std::shared_ptr<AbstractChair> createChair() const override
    {
        return std::make_shared<ChairModernStyle>();
    }

    std::shared_ptr<AbstractSofa> createSofa() const override
    {
        return std::make_shared<SofaModernStyle>();
    }
};

class ConcreteFurnitureFactoryArtDecoStyle : public AbstractFurnitureFactory
{
    std::shared_ptr<AbstractTable> createTable() const override
    {
        return std::make_shared<TableArtDecoStyle>();
    }

    std::shared_ptr<AbstractChair> createChair() const override
    {
        return std::make_shared<ChairArtDecoStyle>();
    }

    std::shared_ptr<AbstractSofa> createSofa() const override
    {
        return std::make_shared<SofaArtDecoStyle>();
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

// Based on input / config / environment we decide the factory to be used
std::shared_ptr<AbstractFurnitureFactory> readConfig(char* family2Type)
{
    toLowerCase(family2Type);

    if (strcmp(family2Type, "victorian") == 0)
    {
        return std::make_shared<ConcreteFurnitureFactoryVictorianStyle>();
    }
    else if (strcmp(family2Type, "modern") == 0)
    {
        return std::make_shared<ConcreteFurnitureFactoryModernStyle>();
    }
    else if (strcmp(family2Type, "artdeco") == 0)
    {
        return std::make_shared<ConcreteFurnitureFactoryArtDecoStyle>();
    }
    else
    {
        throw std::runtime_error("Invalid style");
    }
}

int main(int argc, char* argv[])
{
    // Use the Abstract Factory when your code needs to work with various families of related products, but you don’t want it to depend on the concrete classes of those products—they might be unknown beforehand or you simply want to allow for future extensibility.
    // Consider implementing the Abstract Factory when you have a class with a set of Factory Methods that blur its primary responsibility.
    
    // Family1: Furniture type
    // Family2: Style Variation

    if (argc == 2)
    {
        try
        {
            std::shared_ptr<AbstractFurnitureFactory> abstractFactory = readConfig(argv[1]);
            
            abstractFactory->createTable()->whatAmI();
            abstractFactory->createChair()->whatAmI();
            abstractFactory->createSofa()->whatAmI();
        }
        catch (const std::exception& ex)
        {
            std::cout << "Exception: " << ex.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid number of input arguments" << std::endl;
    }

    return 0;
}