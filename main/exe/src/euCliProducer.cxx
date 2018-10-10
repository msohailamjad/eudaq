#include "eudaq/OptionParser.hh"
#include "eudaq/Producer.hh"
#include <iostream>

int main(int /*argc*/, const char **argv) {
  eudaq::OptionParser op("EUDAQ Command Line Producer", "2.0", "The producer launcher of EUDAQ");
  eudaq::Option<std::string> name(op, "n", "name", "", "string",
				  "The eudaq application to be launched");
  eudaq::Option<std::string> tname(op, "t", "tname", "", "string",
				  "Runtime name of the eudaq application");
  eudaq::Option<std::string> rctrl(op, "r", "runcontrol", "", "address",
				   "The address of the run control to connect to");
  //  eudaq::Option<std::string> rctrl(op, "r", "runcontrol", "tcp://localhost:44000", "address",
  //  				   "The address of the run control to connect to");
  try{
    op.Parse(argv);

  }
  catch(...){
    std::ostringstream err;
    return op.HandleMainException(err);
  }
  std::string app_name = name.Value();
  if(app_name.find("Producer") == std::string::npos){
    std::cout<<"unknown application"<<std::endl;
    return -1;
  }
  auto app=eudaq::Producer::Make(name.Value(), tname.Value(), rctrl.Value());
  if(!app){
    std::cout<<"unknown Producer: "<<name.Value()<<std::endl;
    return -1;
  }  
  try{
    std::string rctrl_value = rctrl.Value();
    std::cout << rctrl_value << std::endl;
    if(!rctrl_value.empty())
      app->Connect();
    else if(rctrl_value.empty()) {
      std::cout << "Offline Run? " << std::endl;
      app->OfflineRun();
      }
  }
  catch (...){
    std::cout<<"Can not connect to RunControl at "<<rctrl.Value()<<std::endl;
    return -1;
  }
  while(app->IsConnected()){
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}
