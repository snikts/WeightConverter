#include <iostream>
namespace usu
{

    template <typename ratioType, typename storageType = std::uint64_t>
    class weight
    {
      private:
        storageType weightCount;

      public:
        using ratio = ratioType;
        weight()
        {
            weightCount = 0;
        }
        weight(storageType t)
        {
            weightCount = t;
        }
        storageType count() const
        {
            return weightCount;
        }
        weight operator+(weight w)
        {
            weight toReturn;
            toReturn.weightCount = weightCount + w.weightCount;
            return toReturn;
        }
        weight operator-(weight w)
        {
            weight toReturn;
            toReturn.weightCount = weightCount - w.weightCount;
            return toReturn;
        }
        //friend weight weight_cast(weight conversion);
    };

    using microgram = weight<std::ratio<1, 1000000>, double>;
    using gram = weight<std::ratio<1, 1>, double>;
    using kilogram = weight<std::ratio<1000, 1>, double>;
    using ounce = weight<std::ratio<10000000000, 352739619>, double>;
    using pound = weight<std::ratio<10000000000, 22046226>, double>;
    using ton = weight<std::ratio<10000000000, 11023>, double>;

    template <typename W, typename S>
    W operator*(const S lhs, W& rhs)
    {
        W result(lhs * rhs.count());

        return result;
    }

    template <typename W, typename S>
    W operator*(W& lhs, const S rhs)
    {
        W result(lhs.count() * rhs);

        return result;
    }

    template <typename To, typename From>
    To weight_cast(From conversion)
    {
        //conversion -> C
        //To temp;
        double inGrams = conversion.count() * (static_cast<double>(From::ratio::num) / From::ratio::den);
        //std::cout << "in grams: " << inGrams << std::endl;
        double count = (inGrams * (static_cast<double>(To::ratio::den) / To::ratio::num));
        //std::cout << "count: " << count << std::endl;
        To temp(count);
        return temp;
    }

} // namespace usu