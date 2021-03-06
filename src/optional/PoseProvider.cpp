#include "PoseProvider.hpp"

#include <localization/proxies/PoseProvider.hpp>
#include <graph_slam/proxies/VelodyneSLAM.hpp>

namespace init
{


PoseProvider::PoseProvider(VelodyneSlam &slam, PositionProvider &odometry, const std::string &poseProviderTaskName)
    : PositionProvider("PoseProvider")
    , slam(slam)
    , odometry(odometry)
    , poseProviderTask(this, poseProviderTaskName)
{
    registerDependency(slam);
    registerDependency(odometry);
}

bool PoseProvider::connect()
{
    slam.velodyneSlamTask.getConcreteProxy()->pose_provider_update.connectTo(poseProviderTask.getConcreteProxy()->pose_provider_update);
    odometry.getPositionSamples().connectTo(poseProviderTask.getConcreteProxy()->odometry_samples);
    
    return init::Base::connect();
}


OutputProxyPort< base::samples::RigidBodyState >& PoseProvider::getPositionSamples()
{
    return poseProviderTask.getConcreteProxy()->pose_samples;
}

}