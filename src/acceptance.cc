//
// Created by mikhail on 6/16/20.
//

#include <iostream>
#include <chrono>

#include <AnalysisTree/TaskManager.hpp>

#include "sim_acceptance.h"


int main(int n_args, char** args){
  if(n_args<2){
    std::cout << "Error: missing file list operand" << std::endl;
    std::cout << "Please use: ./acceptance file.list" << std::endl;
    return 1;
  }
  std::string list{args[1]};
  AnalysisTree::TaskManager manager({list}, {"hades_analysis_tree"});

  auto *sim_acceptance = new AnalysisTree::SimAcceptance;
  manager.AddTask(sim_acceptance);
  manager.SetOutFileName("out.root");
  manager.Init();
  manager.Run(10);
  manager.Finish();
  return 0;
}