###About Our Product###

IBM streams is capable of processing immense amounts of data and allows the use of ML models to be used. However, these models cannot be trained or updated. Our proposed solution allows for neural networks to be created and trained in real time using IBM streams as a backbone.

Using C++, we built our machine learning APIs to be easily integrated into IBM Streams Analytics. Users can integrate our API with IBM Cloud and develop with StreamStudio, an Eclipse based IDE for IBM Streams. These allow users to easily create their own machine learning models and train them in real time on IBM Streams Platform. With our API, we support
supervised, unsupervised and reinforcement learning.

Our MVP is a simple reinforcement learning agent built upon our API, this agent takes in information from the stock market and predicts whether to buy or sell specific stocks. And most importantly, it learns and improves itself in real time.

By integrating our API with IBM Streams Analytics our customers can build smarter tools for their businesses, especially for those that require reinforcement learning and real time decision making. Potential applications includes weather analytics, healthcare, financial markets, video and audio analytics, and more!

##How to Use Our API##

To use our API, simply include the .cpp/.h files into your project's path and create customized operators that utilizes the API. A simple example could be found in the sample directory.