//
// Created by mikhail on 6/29/20.
//

#include "sim_acceptance.h"
#include <AnalysisTree/DataHeader.hpp>

namespace AnalysisTree {
void SimAcceptance::Init(std::map<std::string, void *> &branch_map) {
  std::cout << "SimAcceptance::Init(): START" << std::endl;
  sim_header_ = static_cast<EventHeader *>(branch_map.at("sim_header"));
  reco_header_ = static_cast<EventHeader *>(branch_map.at("event_header"));
  sim_tracks_ = static_cast<Particles *>(branch_map.at("sim_tracks"));
  double y_axis[16];
  for(int j=0; j<16; ++j){ y_axis[j]=-0.75+0.1* (double) j; }
  double pt_axis[]={0, 0.29375, 0.35625, 0.41875, 0.48125, 0.54375, 0.61875, 0.70625, 0.81875, 1.01875, 2.0};
  v1_even_ = new TProfile2D( "v1_even_10_40pc", ";y_{cm};p_{T}",
                             15, y_axis,
                             10, pt_axis );
  v1_straight_ = new TProfile2D( "v1_(y)_10_40pc", ";y_{cm};p_{T}",
                                 15, y_axis,
                                 10, pt_axis );
  v1_reflected_ = new TProfile2D( "v1_(-y)_10_40pc", ";y_{cm};p_{T}",
                                  15, y_axis,
                                  10, pt_axis );
  std::cout << "SimAcceptance::Init(): RETURN" << std::endl;
}
void SimAcceptance::Exec() {
  std::cout << "SimAcceptance::Exec(): START" << std::endl;
  auto centrality = reco_header_->GetField<float>(
      config_->GetBranchConfig("event_header").GetFieldId("selected_tof_rpc_hits_centrality") );
  if( centrality > 40 )
    return;
  if( centrality < 10 )
    return;

  auto psi_rp = sim_header_->GetField<float>(
      config_->GetBranchConfig("sim_header").GetFieldId("reaction_plane"));
  auto beam_y = data_header_->GetBeamRapidity();
  int n_sim_tracks = sim_tracks_->GetNumberOfChannels();
  for (int i = 0; i < n_sim_tracks; ++i) {
    auto s_track = (sim_tracks_->GetChannel(i));
    if( s_track.GetPid() != 2212 )
      continue;
    auto y = s_track.GetRapidity() - beam_y;
    auto phi = s_track.GetPhi();
    auto pt = s_track.GetPt();
    auto delta_phi = phi - psi_rp;

    v1_straight_->Fill( y, pt, cos(delta_phi) );
    v1_reflected_->Fill( -y, pt, cos(delta_phi) );

    v1_even_->Fill( y, pt, 0.5*cos(delta_phi) );
    v1_even_->Fill( -y, pt, 0.5*cos(delta_phi) );
  }
  std::cout << "SimAcceptance::Exec(): RETURN" << std::endl;
}
void SimAcceptance::Finish() {
  std::cout << "SimAcceptance::Finish(): START" << std::endl;
  v1_straight_->Write();
  v1_reflected_->Write();
  v1_even_->Write();
  std::cout << "SimAcceptance::Finish(): Files are written" << std::endl;
}
} // namespace AnalysisTree