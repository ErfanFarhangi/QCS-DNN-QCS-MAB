# QCS-DNN-QCS-MAB

QoS-Aware 5G Component Selection for Content Delivery in Multi-access Edge Computing

The source code for a QoS-aware 5G-MEC component selection based on the multi-armed bandit algorithm for content delivery is provided. This approach, called QCS-MAB, works by considering each routing path as an arm and selecting the arm with the highest expected reward, which is based on the quality of service experienced by the user. QCS-MAB uses Bayesian techniques to update its beliefs about each arm's expected reward and make real-time decisions. It provides an online learning solution for each UE to determine the optimal routing path by selecting gNB, PSA UPF, and EAS that minimizes latency for the content delivery over time. The obtained routing path is selected in real-time and independently from other UEs. The code is implemented in c++.

The source code for a QoS-aware 5G-MEC component selection based on the deep learning-based approach, called QCS-DNN, is provided and consists of a series of fully connected layers connecting every neuron in one layer to every neuron in another. Through numerical analysis, we establish a neural network for QCS-DNN consisting of four layers: three hidden layers and one output layer. We choose the ReLU activation function for the hidden layers (since it is faster for finding the optimal result) and the Sigmoid activation function for the output layer. We use the standard cross-entropy as the loss function. The optimal 5G-MEC component selection policies obtained from running IP (per different UEs) are used as labeled samples to train the DNN. Once the training of the DNN is completed, we evaluate its performance on the test samples. We assess the network's performance on the unseen 20% of samples we considered separately for the testing phase. The code is implemented in Python.

How to run the QCS-MAB code?

We used visual studio environment to develop the code. You can downlaod visual stuio from https://visualstudio.microsoft.com/downloads/. To run the code using visual studio, you need to first configure visual studio to use IBM CPLEX Concert. Instruction for configuration is availble at https://www.leandro-coelho.com/how-to-configure-ms-visual-studio-to-use-ibm-cplex-concert/

