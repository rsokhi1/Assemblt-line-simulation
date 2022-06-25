// Name: Rajbeer Sokhi
// Seneca Student ID: 124969205 
// Seneca email: rsokhi1@myseneca.ca
// Date of completion: 12/04/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include<iostream>
#include <vector>
#include "CustomerOrder.h"
using namespace std;

namespace sdds {
   size_t CustomerOrder::m_widthField = 0;

   void CustomerOrder::setEmpty() {
      for (size_t i = 0; i < m_cntItem; i++) {
         delete m_lstItem[i];
      }
      delete[] m_lstItem;
   }

   CustomerOrder::CustomerOrder(const std::string& str) {
      Utilities m_util;
      size_t pos = 0;
      bool more = true;
      m_name = m_util.extractToken(str, pos, more);
      m_product = m_util.extractToken(str, pos, more);
      vector<Item*> v_item;
      Item* item{};
      while (more) {
         item = new Item(m_util.extractToken(str, pos, more));
         v_item.push_back(item);
      }
      m_cntItem = v_item.size();
      m_lstItem = new Item * [m_cntItem];
      for (size_t i = 0; i < m_cntItem; i++) {
         m_lstItem[i] = v_item[i];
      }
      m_widthField = m_widthField > m_util.getFieldWidth() ? m_widthField : m_util.getFieldWidth();
   }

   CustomerOrder::CustomerOrder(const CustomerOrder& C) {
      throw string("Copying not allowed for this module!");
   }

   CustomerOrder::CustomerOrder(CustomerOrder&& C) noexcept {
      *this = move(C);
   }

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& C) noexcept {
      if (this != &C) {
         setEmpty();
         m_name = C.m_name;
         m_product = C.m_product;
         m_cntItem = C.m_cntItem;
         m_lstItem = C.m_lstItem;
         C.m_name = "";
         C.m_product = "";
         C.m_cntItem = 0;
         C.m_lstItem = nullptr;
      }
      return *this;
   }
   
   CustomerOrder::~CustomerOrder() {
      setEmpty();
   }

   bool CustomerOrder::isOrderFilled() const {
      bool flag = true;
      for (size_t i = 0; i < m_cntItem && flag; i++) {
         if (m_lstItem[i]->m_isFilled == false) {
            flag = false;
         }
      }
      return flag;
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName) const{
      bool flag = true;
      for (size_t i = 0; i < m_cntItem && flag; i++) {
         if (m_lstItem[i]->m_itemName == itemName) {
            if (m_lstItem[i]->m_isFilled == false) {
               flag = false;
            }
         }
      }
      return flag;
   }

   void CustomerOrder::fillItem(Station& station, ostream& os) {
      bool flag = false;
      for (size_t i = 0; i < m_cntItem && !flag; i++) {
         if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled ) {
            if (station.getQuantity() > 0) {
               station.updateQuantity();
               m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
               m_lstItem[i]->m_isFilled = true;
               flag = true;
               os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
            else {
               os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
         }
      }
   }

   void CustomerOrder::display(ostream& os)const {
      os << m_name << " - " << m_product << endl;
      for (size_t i = 0; i < m_cntItem; i++) {
         os << "[";
         os.fill('0');
         os.width(6);
         os.setf(ios::right);
         os << m_lstItem[i]->m_serialNumber << "] ";
         os.fill(' ');
         os.unsetf(ios::right);
         os.setf(ios::left);
         os.width(m_widthField);
         os << m_lstItem[i]->m_itemName << " - ";
         if (m_lstItem[i]->m_isFilled) {
            os << "FILLED";
         }
         else {
            os << "TO BE FILLED";
         }
         os.unsetf(ios::left);
         os << endl;
      }
   }
}