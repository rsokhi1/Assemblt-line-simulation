// Name: Rajbeer Sokhi
// Seneca Student ID: 124969205 
// Seneca email: rsokhi1@myseneca.ca
// Date of completion: 12/04/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_
#include <string>
#include "Station.h"
namespace sdds {

   class CustomerOrder
   {
      struct Item
      {
         std::string m_itemName;
         size_t m_serialNumber{ 0 };
         bool m_isFilled{ false };

         Item(const std::string& src) : m_itemName(src) {};
      };
      std::string m_name{};
      std::string m_product{};
      size_t m_cntItem{};
      Item** m_lstItem{};
      static size_t m_widthField;
      void setEmpty();
   public:
      CustomerOrder(const std::string& str);
      CustomerOrder(const CustomerOrder& C);
      CustomerOrder& operator=(const CustomerOrder& C) = delete;
      CustomerOrder(CustomerOrder&& C) noexcept;
      CustomerOrder& operator=(CustomerOrder&& C) noexcept;
      ~CustomerOrder();
      bool isOrderFilled() const;
      bool isItemFilled(const std::string& itemName) const;
      void fillItem(Station& station, std::ostream& os);
      void display(std::ostream& os)const;
   };
}

#endif // !SDDS_CUSTOMERORDER_H_
