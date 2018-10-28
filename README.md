Mapping algorithms analyzer
=====================================
As part of the **Hack.Moscow** hackathon, we have prepared a solution to one of the many tracks, the theme of which
is to write an analyzer for clustering algorithms. 

Problem Statement
------------

Imagine you organized a competition between Data Scientists, and they implemented a long list of
algorithms. How would you choose the best one from an extensive library of existing algorithms?

Data is likely going to become less and less structured over time. It is important to understand
which data pieces correspond with each other. 
In particular, when dealing with companies extracted from text, it is advantageous to map them to
a database of companies by name as a first step of structuring such data.
Let's define mapping algorithms as follows:

**({input_company_names}, {internal_company_names}) -> {input_name: internal_name**

Imagine you organized a competition between Data Scientists, and they implemented a long list
of such algorithms.
How would you choose the best one (for some particular dataset or for general usage) from
an extensive library of existing algorithms (in terms of coverage, accuracy, recall, etc.)?
The task for each of you is to develop.

Questions we have tried to answer
---------------------------------------
* How can we evaluate the algorithm without referring to external data?
* What external data can be useful to us?
* Which pipeline will be most convenient for working with data and clusterizers?
* Which metrics are most important in practice?

Evaluating without external sources 
-----------

We used very simple and proven metrics, which despite their simplicity give quite useful
characteristics of the algorithms.

* Average size of clusters 
* Median size of clusters 
* Coefficient Gini 

External data
-----------

We used Yandex and Google search results to calculate a certain score for each algorithm, which
shows the adequacy of its division into clusters.

Pipeline
-----------

We paid much attention to the architecture of the project. The resulting solution is easily
extensible, distributable and simple in design. Below you can see a diagram with modules, each of
which performs its own task.

![Alt text](images/project_model_diagram.png?raw=true "Models")


<p align="right">Authors: Evgenii Kazakov, Nikita Mikhaylov, Dmitrii Zakharov.  Moscow, 2018</p>
