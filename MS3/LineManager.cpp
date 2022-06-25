// Name: Rajbeer Sokhi
// Seneca Student ID: 124969205 
// Seneca email: rsokhi1@myseneca.ca
// Date of completion: 12/04/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;
namespace sdds {
   LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
      string line, cws, nws;
      bool flag;
      size_t pos = 0;
      Utilities util;
      util.setDelimiter('|');
      Workstation* fwstation{};
      Workstation* cwstation{};
      Workstation* nwstation{};
      ifstream fptr(file);
      if (!fptr) {
         throw "Couldn't open file!";
      }
      else {
         while (getline(fptr, line)) {
            cws = util.extractToken(line, pos, flag);
            cwstation = *find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
               return ws->getItemName() == cws;
            });
            m_activeLine.push_back(cwstation);
            if (flag) {
               nws = util.extractToken(line, pos, flag);
               nwstation = *find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                  return ws->getItemName() == nws;
               });
               cwstation->setNextStation(nwstation);
            }
         }
         for_each(stations.begin(), stations.end(), [&](Workstation* st) {
            fwstation = *find_if(stations.begin(), stations.end(), [&](Workstation* stn) {
               return stn->getNextStation() == fwstation;
               });
         });
         m_firstStation = fwstation;
      }
      fptr.close();
      m_cntCustomerOrder = g_pending.size();
   }
   
   void LineManager::reorderStations() {
      vector<Workstation*> tempWs;
      Workstation* tpWs = m_firstStation;
      do {
         tempWs.push_back(tpWs);
         tpWs = tpWs->getNextStation();
      } while (tpWs != nullptr);
      m_activeLine.clear();
      m_activeLine = tempWs;
   }

   bool LineManager::run(ostream& os) 
   {
      static size_t count{};
      
      os << "Line Manager Iteration: " << ++count << endl;
      if (!g_pending.empty()) {
         *m_firstStation += move(g_pending.front());
         g_pending.pop_front();
      }
      for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* ws) {
         ws->fill(os);
         });
      for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* ws) {
         ws->attemptToMoveOrder();
         });
      return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
   }

   void LineManager::display(ostream& os)const {
      for (auto activeL : m_activeLine) {
         activeL->display(os);
      }
   }


}