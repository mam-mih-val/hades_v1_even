//
// Created by mikhail on 6/29/20.
//

#ifndef EFFICIENCY_SRC_SIM_ACCEPTANCE_H_
#define EFFICIENCY_SRC_SIM_ACCEPTANCE_H_

#include <TChain.h>
#include <TProfile2D.h>

#include <AnalysisTree/EventHeader.hpp>
#include <AnalysisTree/FillTask.hpp>
#include <AnalysisTree/Cuts.hpp>
#include <AnalysisTree/Detector.hpp>

#include <TH3F.h>
#include <centrality.h>

namespace AnalysisTree {
class SimAcceptance : public FillTask {
public:
  void Init(std::map<std::string, void *> &branch_map) override;
  void Exec() override;
  void Finish() override;

private:
  EventHeader *sim_header_{nullptr};
  EventHeader *reco_header_{nullptr};
  Particles *sim_tracks_{nullptr};

  TProfile2D* v1_even_;
  TProfile2D* v1_straight_;
  TProfile2D* v1_reflected_;
};
} // namespace AnalysisTree
#endif // EFFICIENCY_SRC_SIM_ACCEPTANCE_H_
