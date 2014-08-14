#ifndef PIXTESTALIVE_H
#define PIXTESTALIVE_H

#include "PixTest.hh"

class DLLEXPORT PixTestAlive: public PixTest {
public:
  PixTestAlive(PixSetup *, std::string);
  PixTestAlive();
  virtual ~PixTestAlive();
  virtual bool setParameter(std::string parName, std::string sval); 
  void init(); 
  void setToolTips();
  void bookHist(std::string); 

  void runCommand(std::string); 
  void aliveTest();
  void maskTest();
  void addressDecodingTest();

  void doTest(); 
  void output4moreweb();

private:

  uint16_t fParNtrig; 
  int      fParVcal; 

  ClassDef(PixTestAlive, 1)

};
#endif
