/**
@file  BasicThermal.cpp
@brief BasicThermal GUNNS Basic Network implementation.

@copyright  Copyright 2019 United States Government as represented by the Administrator of the
            National Aeronautics and Space Administration. All Rights Reserved.

LIBRARY DEPENDENCY:
(
  (core/GunnsBasicConductor.o)
  (core/GunnsBasicPotential.o)
  (core/network/GunnsNetworkBase.o)
)

PROGRAMMERS:
  ((Auto-generated by the GunnsDraw netexport script version 19.3.7) (2022-08-22 23:15:51.922548))
*/

#include "BasicThermal.hh"
#include "simulation/hs/TsHsMsg.hh"
#include "software/exceptions/TsInitializationException.hh"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] name    (--) Name of the network for H&S messages.
/// @param[in] network (--) Pointer to the main network object.
/// 
/// @details  Default constructs the BasicThermal Network Config Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
BasicThermalConfigData::BasicThermalConfigData(const std::string& name, BasicThermal* network)
    :
    netSolver(name + ".netSolver", 0.001, 0.001, 10.0000, 1),
    // Spotter Config Data
    // Link Config Data
    SimpleVoltageSource(name + ".SimpleVoltageSource", &network->netNodeList, 0.01),
    Resistor1(name + ".Resistor1", &network->netNodeList, 1e-05),
    Resistor2(name + ".Resistor2", &network->netNodeList, 1e-06)
{
    // Load config data vectors
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs the BasicThermal Network Config Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
BasicThermalConfigData::~BasicThermalConfigData()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] network (--) Pointer to the main network object.
///
/// @details  Default constructs the BasicThermal Network Input Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
BasicThermalInputData::BasicThermalInputData(BasicThermal* network)
    :
    // Spotter Input Data
    // Link Input Data
    SimpleVoltageSource(false, 0.0, 120),
    Resistor1(false, 0.0),
    Resistor2(false, 0.0)
{
    // Load input data vectors
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs the BasicThermal Network Input Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
BasicThermalInputData::~BasicThermalInputData()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] name (--) Name of the network for H&S messages.
///
/// @details  Default constructs the BasicThermal Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
BasicThermal::BasicThermal(const std::string& name)
    :
    GunnsNetworkBase(name, N_NODES, netNodes),
    netNodes(),
    netConfig(name, this),
    netInput(this),
    // Data Tables 
    // Spotters
    // Links
    SimpleVoltageSource(),
    Resistor1(),
    Resistor2()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details Default destructs the BasicThermal Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
BasicThermal::~BasicThermal()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] name (--) Name of the network for H&S messages.
///
/// @details  Initializes the nodes with their config and input data objects.  The nodes are
///           initialized through the node list object, which may point to this network's nodes
///           (when this is a standalone network), or the super-network's nodes (as a sub-network).
////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicThermal::initNodes(const std::string& name)
{
    /// - Initialize the nodes.
    netNodeList.mNodes[0 + netSuperNodesOffset].initialize(name + createNodeName(0 + netSuperNodesOffset), 120.0);
    netNodeList.mNodes[1 + netSuperNodesOffset].initialize(name + createNodeName(1 + netSuperNodesOffset), 120.0);
    /// - Only init the Ground node if this is not a sub-network.
    if (!netIsSubNetwork) {
        netNodeList.mNodes[2].initialize(name + ".GROUND");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Initializes this network's links, spotters and solver with their config and input data
///           objects.
////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicThermal::initNetwork()
{
    const int groundOffset = netNodeList.mNumNodes - N_NODES;

    /// - Register sockets with the jumper plugs.

    /// - Initialize the links.
    netLinks.clear();
    SimpleVoltageSource.initialize(netConfig.SimpleVoltageSource, netInput.SimpleVoltageSource, netLinks, GROUND + groundOffset, Node0 + netSuperNodesOffset);
    Resistor1.initialize(netConfig.Resistor1, netInput.Resistor1, netLinks, Node0 + netSuperNodesOffset, Node1 + netSuperNodesOffset);
    Resistor2.initialize(netConfig.Resistor2, netInput.Resistor2, netLinks, Node1 + netSuperNodesOffset, GROUND + groundOffset);

    /// - Initialize the spotters.

    /// - Initialize the solver, only if this is not a sub-network.
    if (!netIsSubNetwork) {
        netSolver.initializeNodes(netNodeList);
        netSolver.initialize(netConfig.netSolver, netLinks);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] timeStep (s) Integration time step.
///
/// @details  Updates this network's spotters before solving the network.
////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicThermal::stepSpottersPre(const double timeStep)
{
    /// - Step network spotters prior to solver step.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in]   timeStep (s) Integration time step.
///
/// @details  Updates this network's spotters after solving the network.
////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicThermal::stepSpottersPost(const double timeStep)
{
    /// - Step network spotters after solver step.
}
