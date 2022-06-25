// Name: Rajbeer Sokhi
// Seneca Student ID: 124969205 
// Seneca email: rsokhi1@myseneca.ca
// Date of completion: 12/04/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_
#include <deque>
#include "CustomerOrder.h"

namespace sdds {
   extern std::deque<CustomerOrder> g_pending;
   extern std::deque<CustomerOrder> g_completed;
   extern std::deque<CustomerOrder> g_incomplete;

   class Workstation : public Station {
      std::deque<CustomerOrder> m_orders{};
      Workstation* m_pNextStation{};
   public:
      Workstation(const std::string& str);
      Workstation(const Workstation& W) = delete;
      Workstation(Workstation&& W) = delete;
      Workstation& operator=(const Workstation& W) = delete;
      Workstation& operator=(Workstation&& W) = delete;
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder&& newOrder);
   };
}

#endif // !SDDS_WORKSTATION_H_
