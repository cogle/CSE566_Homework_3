
## Problem 1
<p>
In this problem we will analyze multiple factors and how they influence the
performance of our code. We will divide this performance analysis into three
sections. The first section will look at the performance of simply running the
program locally. The second section will look at how the program performs on the
WUSTL cluster. Finally we will compare our results from the local run and the
cluster runs and measure the differences in performance.
</p>

### Section 1

#### Test 1
<p>
In this test we will be holding the **number of stars**, **starmass** and **t_final**
constant while manipulating the **number of nodes**.
</p>
<p>
The test will be ran with the following parameters 
**mpiexec -n VARIABLE ./a.out 1024 200.0 5000 0**
</p>


```python
import plotly.plotly as py
import plotly.graph_objs as go
from plotly.tools import FigureFactory as FF 

# Create random data with numpy
import numpy as np
x0 = ['1', '2', '3' ,'4', '5', '6', '7',
     '8', '9', '10' ,'11', '12', '13', '14',
     '15', '16', '18' ,'20', '24', '28', '32',
     '36', '40', '44' ,'48']
#CPU events registered, pulled from results folder
y0 = [31.380487,31.091134,31.218060,31.032758,31.150756]
y1 = [33.244369,34.670849,35.841239,34.807071,35.098124]
y2 = [23.832296,23.944820,23.738924,23.777542,23.685885]
y3 = [18.148244,18.453097,17.963263,18.040154,18.049262]
y4 = [14.606364,14.941448,15.007499,14.895093,14.975426]
y5 = [12.760485,12.590689,12.602171,12.638109,12.602006]
y6 = [11.268891,11.173316,11.155241,11.015657,11.006935]
y7 = [9.799989,9.753002,9.746926,9.802207,9.801208]
y8 = [9.171935,9.180143,9.226501,9.076801,8.995206]
y9 = [8.264486,8.223048,8.524570,8.219817,8.206178]
y10 = [7.457435,7.404798,7.400088,7.441416,7.423261]
y11 = [7.171395,7.127962,7.966452,7.105859,7.619809]
y12 = [10.916491,10.974141,11.004193,10.536253,10.879966]
y13 = [11.996442,11.967475,12.316837,12.076440,12.040178]
y14 = [12.547808,13.350146,13.675628,12.880463,13.016381]
y15 = [13.557813,14.216631,13.987904,13.919366,15.339166]
y18 = [8.313894,8.261919,8.618369,8.400106,8.105080]
y20 = [7.899661,7.376515,7.643994,7.932702,7.397855]
y24 = [6.878949,8.617733,7.033754,7.801950,6.372911]
y28 = [6.987169,7.280790,7.088979,7.496430,7.024330]
y32 = [7.203131,7.154219,7.515005,7.011300,6.797571]
y36 = [7.445983,7.353207,7.320933,7.029041,7.444723]
y40 = [7.576035,8.505020,7.557124,7.487863,7.005769]
y44 = [7.166438,7.701247,7.657546,7.330243,8.126713]
y48 = [7.944982,7.865770,6.968336,8.001566,8.012780]

y_graph = [np.average(y0),
           np.average(y1),
           np.average(y2),
           np.average(y3),
           np.average(y4),
           np.average(y5),
           np.average(y6),
           np.average(y7),
           np.average(y8),
           np.average(y9),
           np.average(y10),
           np.average(y11),
           np.average(y12),
           np.average(y13),
           np.average(y14),
           np.average(y15),
           np.average(y18),
           np.average(y20),
           np.average(y24),
           np.average(y28),
           np.average(y32),
           np.average(y36),
           np.average(y40),
           np.average(y44),
           np.average(y48)
          ]


# Create traces
trace0 = go.Scatter(
    x = x0,
    y = y_graph,
    mode = 'lines+markers',
    error_y=dict(
        type='data',
        array=[
              np.std(y0),
              np.std(y1),
              np.std(y2),
              np.std(y3),
              np.std(y4),
              np.std(y5),
              np.std(y6),
              np.std(y7),
              np.std(y8),
              np.std(y9),
              np.std(y10),
              np.std(y11),
              np.std(y12),
              np.std(y13),
              np.std(y14),
              np.std(y15),
              np.std(y18),
              np.std(y20),
              np.std(y24),
              np.std(y28),
              np.std(y32),
              np.std(y36),
              np.std(y40),
              np.std(y44),
              np.std(y48)
              ],
        visible=True
    )
)

data = [trace0]
layout=go.Layout(height=1000,
                 title="Local: Time to run vs Number of nodes", 
                 xaxis={'title':'Number of Nodes'}, 
                 yaxis={'title':'Time(sec)'})

figure=go.Figure(data=data,layout=layout)
py.iplot(figure, filename='Local-Node')
```




<iframe id="igraph" scrolling="no" style="border:none;" seamless="seamless" src="https://plot.ly/~cogle/29.embed" height="1000px" width="100%"></iframe>



<div>
    <a href="https://plot.ly/~cogle/29/" target="_blank" 
       title="OpenMP: Time to run vs Optimization" 
       style="display: block; text-align: center;">
       
        <img src="https://plot.ly/~cogle/29.png" alt="OpenMP: Time to run vs Optimization" 
             style="max-height:1000"  
             onerror="this.onerror=null;this.src='https://plot.ly/404.png';" />
    </a>
    <script data-plotly="cogle:29"  src="https://plot.ly/embed.js" async></script>
</div>

### Local Cluster Node Dependency Analysis
<p>
The results of running the test are above. From these results I see two points 
of interest that will be the focus of this section's discussion.
</p>
<p>
The first point of interest is that it is faster to run the code on average
as single process rather than use two. Now I will admit that the variance for
running it as a single process is much greater and exceeds the time for running
it with two processes; however on average its faster. This is interesting
because I would have thought that no matter what using two process would be
faster. 
</p>

<p>
The second point of interest is something that I noticed last time when running
the test. The mysterious bump has returned yet again, and in the exact same
spot. This is really interesting and exciting. This is definitely hinting at a
weak spot with regards to the chip. After having ran two separate high
performance libraries both of them demonstrated a slow down over the same range.
This really makes me wonder how these processes are being created and handled by
the chip. In the previous assignment I attributed the poor performance in this
range due to the fact that our chip is actually only physically 8 cores, yet
through Hyper Threading it can pretend like it has 16 Threads. However, this
code is using a message passaging system, which does not rely on threads, but
rather is dependent upon processes. I am now beginning to wonder if this is a
scheduling problem and not so much a hardware problem. The reason I say this is
because like in the previous assignment the performance returns to near pre-hump
levels after clearing 18 cores. It is really interesting that this hump would
appear again in our results.
</p>

#### Test 2
<p>
In this test we will be holding the **number of cores**, **starmass** and **t_final**
constant while manipulating the ** number of stars**.
</p>
<p>
The test will be ran with the following parameters 
**mpiexec -n 8 ./a.out VARIABLE 200.0 5000 0**
</p>

#### Hypothesis
<p>
Having looked at the code in both dervis.cpp and dervis_client.cpp, the 
algorithm relies on a O(n^2) for loop in order to iterate through all assigned 
points. Therefore since each process is assigned a portion of the stars to 
iterate through in a O(n^2) loop as we increase the number of stars the time to
complete will increase too in an O(n^2) manner. 
</p>


```python
import plotly.plotly as py
import plotly.graph_objs as go
from plotly.tools import FigureFactory as FF 

import numpy as np

x0 = ['500', '1000', '1500' ,'2000', 
      '2500', '3000', '3500',
      '4000','4500','5000', '5500']

#CPU events registered, pulled from results folder

#500
y0 = [2.469005,2.490445,2.491086,2.463654,2.435809]
#1000
y1 = [9.308746,9.331429,9.309926,9.380380,9.340391]
#1500
y2 = [20.892919,20.848614,20.854890,20.897508,20.874032]
#2000
y3 = [36.803694,36.719265,36.852905,36.857804,36.849287]
#2500
y4 = [57.389636,57.773187,57.412680,57.457165,57.019039]
#3000
y5 = [82.051955,82.436075,82.402073,82.338356,82.312260]
#3500
y6 = [112.122695,112.138879,112.492952,112.376010,112.184795]
#4000
y7 = [146.311898,146.158862,146.277270,146.124294,146.204294]
#4500
y8 = [185.263980,184.937304,185.090751,185.308805,184.791915]
#5000
y9= [227.908076,227.886200,229.163210,227.723492,228.133204]
#5500
y10= [276.139815,276.155828,276.092563,275.990451,276.023360]

y_graph = [np.average(y0),
           np.average(y1),
           np.average(y2),
           np.average(y3),
           np.average(y4),
           np.average(y5),
           np.average(y6),
           np.average(y7),
           np.average(y8),
           np.average(y9),
           np.average(y10)
          ]


# Create traces
trace0 = go.Scatter(
    x = x0,
    y = y_graph,
    mode = 'lines+markers',
    name = 'r = vM (Default)',
    error_y=dict(
        type='data',
        array=[
              np.std(y0),
              np.std(y1),
              np.std(y2),
              np.std(y3),
              np.std(y4),
              np.std(y5),
              np.std(y6),
              np.std(y7),
              np.std(y8),
              np.std(y9),
              np.std(y10)
              ],
        visible=True
    )
)

data = [trace0]
layout=go.Layout(height=1000,
                 title="Local: Time to run vs Number of stars", 
                 xaxis={'title':'Number of Stars'}, 
                 yaxis={'title':'Time(sec)'})

figure=go.Figure(data=data,layout=layout)
py.iplot(figure, filename='Local-Stars')
```




<iframe id="igraph" scrolling="no" style="border:none;" seamless="seamless" src="https://plot.ly/~cogle/31.embed" height="1000px" width="100%"></iframe>



<div>
    <a href="https://plot.ly/~cogle/31/" target="_blank" 
       title="OpenMP: Time to run vs Optimization" 
       style="display: block; text-align: center;">
       
        <img src="https://plot.ly/~cogle/31.png" alt="OpenMP: Time to run vs Optimization" 
             style="max-height:1000"  
             onerror="this.onerror=null;this.src='https://plot.ly/404.png';" />
    </a>
    <script data-plotly="cogle:31"  src="https://plot.ly/embed.js" async></script>
</div>

### Local Cluster Star Dependency Analysis
<p>
So from the graph we don't really see any surprises like we saw in the previous
section. From this test I really didn't expect to see any surprises as this test
is simply manipulating the variables of the program and not hardware
configurations. I might of expected a sharper increase in the time it takes as
the number of stars increased because now we have much more information that we
have to transfer amongst processes. Therefore due to latency in the
communication system, a factor of the problem out of our control, it would take
longer to pass all that information from one place to the next. However, I am
please with this graph and the way that it looks. 
</p>

#### Test 3
<p>
In this test we will be holding the **number of cores**, **starmass** and **number of stars**
constant while manipulating the **t_final**.
</p>
<p>
The test will be ran with the following parameters 
**mpiexec -n 8 ./a.out 1024 200.0 VARIABLE 0**
</p>

#### Hypothesis
<p>
In this problem the code of interest resides in Gal.cpp, this code is 
executed by the server process. Since we are holding all other variables in the
problem constant I predict that this graph will be linear. 
</p>


```python
import plotly.plotly as py
import plotly.graph_objs as go
from plotly.tools import FigureFactory as FF 

import numpy as np

x0 = [
      '100','200','300','400','500','750',
      '1000', '1500', '2000', '2500', '3000',
      '3500', '4000', '4500', '5000', '7500',
      '10000', '12500', '15000'
     ]


y0  = [0.244141,0.244308,0.272929,0.243987,0.244349]
y1  = [0.467116,0.464244,0.468063,0.467573,0.496308]
y2  = [0.663809,0.656124,0.659188,0.670299,0.658984]
y3  = [0.848656,0.863760,0.861470,0.861480,0.852968]
y4  = [1.049963,1.053150,1.051004,1.052064,1.045944]
y5  = [1.495537,1.546982,1.513957,1.591083,1.598137]
y6  = [1.987113,2.026296,2.009545,2.048171,2.045885]
y7  = [2.998860,2.987037,2.985883,2.984040,3.031294]
y8  = [4.032151,3.965394,3.947855,3.947081,3.968865]
y9  = [4.937260,4.901123,4.939154,4.944908,4.933745]
y10 = [5.992963,5.828659,5.926617,6.028237,6.050239]
y11 = [6.963962,6.862333,6.833764,6.843262,6.847927]
y12 = [7.797002,7.805201,7.840804,7.839545,7.812171]
y13 = [8.815890,8.801186,9.000007,8.840439,8.807733]
y14 = [9.801725,9.809385,9.820659,9.812974,9.811488]
y15 = [14.646719,14.711875,14.608548,14.642289,14.726290]
y16 = [19.455623,19.488748,19.517233,19.356202,19.552424]
y17 = [25.460980,24.292701,24.451065,24.296073,24.274980]
y18 = [29.135910,29.104393,29.193547,29.150248,29.316022]

y_graph = [np.average(y0),
           np.average(y1),
           np.average(y2),
           np.average(y3),
           np.average(y4),
           np.average(y5),
           np.average(y6),
           np.average(y7),
           np.average(y8),
           np.average(y9),
           np.average(y10),
           np.average(y11),
           np.average(y12),
           np.average(y13),
           np.average(y14),
           np.average(y15),
           np.average(y16),
           np.average(y17),
           np.average(y18)
           ]


# Create traces
trace0 = go.Scatter(
    x = x0,
    y = y_graph,
    mode = 'lines+markers',
    name = 'r = vM (Default)',
    error_y=dict(
        type='data',
        array=[
              np.std(y0),
              np.std(y1),
              np.std(y2),
              np.std(y3),
              np.std(y4),
              np.std(y5),
              np.std(y6),
              np.std(y7),
              np.std(y8),
              np.std(y9),
              np.std(y10),
              np.std(y11),
              np.std(y12),
              np.std(y13),
              np.std(y14),
              np.std(y15),
              np.std(y16),
              np.std(y17),
              np.std(y18)
              ],
        visible=True
    )
)

data = [trace0]
layout=go.Layout(height=1000,
                 title="Local: Time to run vs Steps", 
                 xaxis={'title':'Number of Steps'}, 
                 yaxis={'title':'Time(sec)'})

figure=go.Figure(data=data,layout=layout)
py.iplot(figure, filename='Local-T')
```




<iframe id="igraph" scrolling="no" style="border:none;" seamless="seamless" src="https://plot.ly/~cogle/33.embed" height="1000px" width="100%"></iframe>



<div>
    <a href="https://plot.ly/~cogle/33/" target="_blank" 
       title="OpenMP: Time to run vs Optimization" 
       style="display: block; text-align: center;">
       
        <img src="https://plot.ly/~cogle/33.png" alt="OpenMP: Time to run vs Optimization" 
             style="max-height:1000"  
             onerror="this.onerror=null;this.src='https://plot.ly/404.png';" />
    </a>
    <script data-plotly="cogle:33"  src="https://plot.ly/embed.js" async></script>
</div>

### Local Cluster Step Dependency Analysis
<p>
Again we don't see any surprises here the algorithm behaves as the hypothesis
outlined. I don't think message passing latency would come into play in this 
scenario since we are really dealing with a small number of messages being 
passed between the processes. If I had increased the number of stars while 
keeping the nodes constant and the steps, while the line would be linear it is
my belief that it would begin to take on a more quadratic look as the transfer 
of data begins to take a non-negligible amount of time. 
</p>

### Section 2
<p>
In this section we will be running the first test from above on the WUSTL cluster.
The reason I will only run the first test is since I used 8 cores everything will be assigned
to a single machine. Therefore the only test that highlights the performance of using multiple
processes is the first one. 
However I will run additional test in order to compare the speed difference of running larger
more complicated problems on the cluster, and how that compares to running the same task locally.
</p>

#### Test 1

#### Hypothesis
<p>
So based on the previous test I already know what the graph should look like. So
therefore I will hypothesize about how much faster/slower I think the cluster 
will be. I think that the cluster will be faster, at least once we get past 20 
cores. My thought is the cluster is designed for this purpose so it should be 
faster.
</p>


```python
import plotly.plotly as py
import plotly.graph_objs as go
from plotly.tools import FigureFactory as FF 

# Create random data with numpy
import numpy as np
x0 = ['1', '2', '3' ,'4', '5', '6', '7',
     '8', '9', '10' ,'11', '12', '13', '14',
     '15', '16', '18' ,'20', '24', '28', '32',
     '36', '40', '44' ,'48']
#CPU events registered, pulled from results folder
y0 = [32.924338,32.840351,30.742163,34.399434,30.702516]
y1 = [106.041384,36.328952,35.495616,34.329675,106.301041]
y2 = [25.844808,23.660780,23.712212,52.802516,25.976857]
y3 = [19.132214,18.639792,18.472374,19.659601,19.787322]
y4 = [14.897115,15.431824,15.957574,16.077706,16.599138]
y5 = [13.105356,13.046708,12.928091,13.401004,13.403940]
y6 = [11.453944,11.506693,11.479313,11.454754,11.489004]
y7 = [54.071547,35.293484,37.893740,37.763534,38.585893]
y8 = [9.155187,9.126825,9.128926,13.347799,9.203470]
y9 = [13.317543,21.346074,17.844512,8.422438,15.945211]
y10 = [7.535906,11.524401,11.265689,10.499955,14.593886]
y11 = [7.930292,11.895504,18.261792,14.425395,21.940836]
y12 = [31.514334,9.700754,7.531323,6.518291,8.851042]
y13 = [24.891219,8.869963,19.979515,21.596686,23.924366]
y14 = [16.798375,11.919620,20.577216,18.993536,21.203789]
y15 = [26.024765,26.103651,9.632740,16.896646,19.796719]
y18 = [19.229071,12.244432,10.266115,20.732357,6.023942]
y20 = [15.366584,12.953202,17.545329,17.837286,9.409448]
y24 = [15.622001,14.015448,15.436493,12.445456,6.988156]
y28 = [7.785333,13.419809,8.496837,12.435327,19.113864]
y32 = [11.074475,13.765365,10.765662,13.895603,11.578424]
y36 = [17.435614,16.480547,15.167732,15.760943,11.728238]
y40 = [12.696191,12.949865,15.341082,12.869300,15.846039]
y44 = [13.223730,13.835434,13.573091,13.316146,16.037211]
y48 = [14.791206,14.785884,14.292008,14.322461,14.527391]

y_graph = [np.average(y0),
           np.average(y1),
           np.average(y2),
           np.average(y3),
           np.average(y4),
           np.average(y5),
           np.average(y6),
           np.average(y7),
           np.average(y8),
           np.average(y9),
           np.average(y10),
           np.average(y11),
           np.average(y12),
           np.average(y13),
           np.average(y14),
           np.average(y15),
           np.average(y18),
           np.average(y20),
           np.average(y24),
           np.average(y28),
           np.average(y32),
           np.average(y36),
           np.average(y40),
           np.average(y44),
           np.average(y48)
          ]


# Create traces
trace0 = go.Scatter(
    x = x0,
    y = y_graph,
    mode = 'lines+markers',
    error_y=dict(
        type='data',
        array=[
              np.std(y0),
              np.std(y1),
              np.std(y2),
              np.std(y3),
              np.std(y4),
              np.std(y5),
              np.std(y6),
              np.std(y7),
              np.std(y8),
              np.std(y9),
              np.std(y10),
              np.std(y11),
              np.std(y12),
              np.std(y13),
              np.std(y14),
              np.std(y15),
              np.std(y18),
              np.std(y20),
              np.std(y24),
              np.std(y28),
              np.std(y32),
              np.std(y36),
              np.std(y40),
              np.std(y44),
              np.std(y48)
              ],
        visible=True
    )
)

data = [trace0]
layout=go.Layout(height=1000,
                 title="Cluster: Time to run vs Number of nodes", 
                 xaxis={'title':'Number of Nodes'}, 
                 yaxis={'title':'Time(sec)'})

figure=go.Figure(data=data,layout=layout)
py.iplot(figure, filename='Cluster-Node')
```




<iframe id="igraph" scrolling="no" style="border:none;" seamless="seamless" src="https://plot.ly/~cogle/35.embed" height="1000px" width="100%"></iframe>



<div>
    <a href="https://plot.ly/~cogle/35/" target="_blank" 
       title="OpenMP: Time to run vs Optimization" 
       style="display: block; text-align: center;">
       
        <img src="https://plot.ly/~cogle/35.png" alt="OpenMP: Time to run vs Optimization" 
             style="max-height:1000"  
             onerror="this.onerror=null;this.src='https://plot.ly/404.png';" />
    </a>
    <script data-plotly="cogle:35"  src="https://plot.ly/embed.js" async></script>
</div>

### Cluster Node Dependency Analysis
<p>
Looking at this graph and comparing it to the previous graph it is quite a
contrast. The first thing that I noticed as I was entering in the number is that
the amount of variance for each run was much, much greater than that of running
it locally. Second thing I notice is my hypothesis was wrong.
When running the test with a lower number of runs it seems that
despite being on the same core the variance in time is much greater. I wonder if
this is a side-effect of running the code on the cluster. In addition to having
to run our program other programs may be running on the same core. Another thing
is that since this is a cluster environment each CPU may have a larger overhead,
that is the CPU may be doing more tasks such as communicating with other nodes
in the cluster, as opposed to when we are running locally we can be pretty much
sure that our process is the only one running.
</p>

<p>
Overall the node does project a downward trend. The problem that was utilized
in the test may not have been best suited for this type of experiment. The
problem could be easily solved with a single machine and doesn't highlight the
advantages, if any, of using a cluster. Therefore in order to demonstrate what
advantages may come from using a cluster in order to solve a complex problem,
another more strenuous test will be ran. It was slightly surprising to me that
using 48 cores on the cluster about two times slower than that of just running
it locally. Based on these results I think that the large amount of 
communication and small problem size does not demonstrate the cluster's full 
potential.
</p>

### Section 3
<p>
In this section we will look at the performance of the cluster versus running 
locally on a much larger problem size. In the above problem surprisingly it is
not the cluster that won out in our test. Rather running the problem locally 
proved to be much faster. I think that this might come from the fact that the 
problem size is very small. When running a much more computationally intensive
problem it is my belief that the cluster will perform better than running the 
problem locally. My reasoning is as follows, when having to run a much more 
computational problem while trying to use many clusters will yield poor 
performance because of scheduling. When running locally each process can only 
run for a certain amount of time before being swapped out. This means that with 
many processes and lots of work to do there will be processes sitting idle while
other processes are working. Then if the processes that are working finish the 
task they now must wait on the idle processes to finish their task when their 
turn comes. This in turn leads to lots of waits. With the cluster each process
is running at all times as each one has a dedicated core. Therefore I believe
with complex problems the cluster will run faster. 
</p>

#### Command Parameters
<p>Number of stars: 5000</p> 
<p>Star mass: 200.0</p>
<p>T Final: 10000</p>


```python
import plotly.plotly as py
import plotly.graph_objs as go
from plotly.tools import FigureFactory as FF 

# Create random data with numpy
import numpy as np
x0 = ['24','26','30','34','38','42','46','50']

y0_local = [442.243320,353.979801,412.598660,376.086102,352.529204]
y1_local = [338.288989,363.792633,306.756777,307.200656,296.780143]
y2_local = [375.473943,362.444366,435.574954,333.132262,335.189970]
y3_local = [350.120001,319.774519,319.219230,326.686066,327.028635]
y4_local = [390.953147,312.178205,306.317485,311.284500,314.255747]
y5_local = [295.715792,291.118734,293.178659,290.994557,296.395328]
y6_local = [312.752324,313.048683,316.486853,314.884665,313.936940]
y7_local = [309.328987,310.570718,313.789085,303.441930,312.066977]


y0_cluster = [494.853427,460.880861,470.588432,471.424171,501.287162]
y1_cluster = [506.038868,604.103987,524.620066,513.691882,575.629832]
y2_cluster = [339.836600,299.520710,367.141345,271.372420,272.088103]
y3_cluster = [344.405668,315.726751,291.508347,291.491026,287.426819]
y4_cluster = [261.127806,298.075168,267.534927,303.706554,229.268512]
y5_cluster = [187.048640,274.648344,240.469243,261.743093,264.184515]
y6_cluster = [201.628926,262.425270,186.095362,264.727925,266.043176]
y7_cluster = [153.779846,162.031731,167.049816,174.921041,160.144198]



y_grap1 = [np.average(y0_local),
           np.average(y1_local),
           np.average(y2_local),
           np.average(y3_local),
           np.average(y4_local),
           np.average(y5_local),
           np.average(y6_local),
           np.average(y7_local)
          ]

y_grap2 = [np.average(y0_cluster),
           np.average(y1_cluster),
           np.average(y2_cluster),
           np.average(y3_cluster),
           np.average(y4_cluster),
           np.average(y5_cluster),
           np.average(y6_cluster),
           np.average(y7_cluster)
          ]



# Create traces
trace0 = go.Scatter(
    x = x0,
    y = y_grap1,
    mode = 'lines+markers',
    name = 'Local',
    error_y=dict(
        type='data',
        array=[
              np.std(y0_local),
              np.std(y1_local),
              np.std(y2_local),
              np.std(y3_local),
              np.std(y4_local),
              np.std(y5_local),
              np.std(y6_local),
              np.std(y7_local),
              ],
        visible=True
    )
)


trace1 = go.Scatter(
    x = x0,
    y = y_grap2,
    mode = 'lines+markers',
    name = 'Cluster',
    error_y=dict(
        type='data',
        array=[
              np.std(y0_cluster),
              np.std(y1_cluster),
              np.std(y2_cluster),
              np.std(y3_cluster),
              np.std(y4_cluster),
              np.std(y5_cluster),
              np.std(y6_cluster),
              np.std(y7_cluster),
              ],
        visible=True
    )
)


data = [trace0, trace1]
layout=go.Layout(height=1000,
                 title="Runtime Execution vs. Cluster or Local Submission", 
                 xaxis={'title':'Number of Nodes'}, 
                 yaxis={'title':'Time(sec)'})

figure=go.Figure(data=data,layout=layout)
py.iplot(figure, filename='Cluster-vs-Local-Node')
```




<iframe id="igraph" scrolling="no" style="border:none;" seamless="seamless" src="https://plot.ly/~cogle/37.embed" height="1000px" width="100%"></iframe>



<div>
    <a href="https://plot.ly/~cogle/37/" target="_blank" 
       title="OpenMP: Time to run vs Optimization" 
       style="display: block; text-align: center;">
       
        <img src="https://plot.ly/~cogle/37.png" alt="OpenMP: Time to run vs Optimization" 
             style="max-height:1000"  
             onerror="this.onerror=null;this.src='https://plot.ly/404.png';" />
    </a>
    <script data-plotly="cogle:37"  src="https://plot.ly/embed.js" async></script>
</div>

<h3>Cluster Versus Local Runtime Analysis</h3>
<p>
Above is the data gathered from various runs both on the cluster and on the l
local machines. What is really interesting to me is that the cluster is actually
not as fast as I thought it would be. Yes in the end the cluster is much faster
method of running code, however it was not an instantaneous winner. Running the
code locally on your machine performed very well up until around 30 cores. Then 
the cluster's power really began to show. Another thing that also surprised me
is that the time it took for the local code to was relatively stable as the 
cores increased. I would have expected a sharp increase in the time it took as
the CPU would become laden with many task all dependent on each others 
completion.  The speed with which the final test ran demonstrates the power of
the cluster when solving a complex problem. 
<p>

### Enhancing the code
<p>
I will admit I was really unable to get much performance gain out of the code 
without having to tweak the optimization level. It actually looked like using 
OpenMP was actually not beneficial in some cases. The reason being is that we 
are already subdividing the problem across different CPU's. Adding in and the 
further distributing the problem with a very small problem and a large number of
nodes will most likely hinder performance. The reason being we have to pay for 
OpenMP to start up, after doing so we assign the spawned threads a chunk of work
if this chunk happens to be small then the spawning all these threads becomes a 
hinderance, rather than a performance benefit. 
</p>


```python
import plotly.plotly as py
import plotly.graph_objs as go
from plotly.tools import FigureFactory as FF 

# Create random data with numpy
import numpy as np
x0 = ['1', '2', '3' ,'4', '5', '6', '7',
     '8', '9', '10' ,'11', '12', '13', '14',
     '15', '16', '18' ,'20', '24', '28']
	 
#CPU events registered, pulled from results folder
y0 = [9.321898,9.088334,9.047898,8.906696,9.053812]
y1 = [9.502416,9.363267,9.060932,9.251514,9.383294]
y2 = [6.265155,6.287955,6.332007,6.365997,6.237368]
y3 = [4.900268,4.806036,4.785335,4.783883,4.801496]
y4 = [3.984377,3.908925,3.913189,3.892003,4.009590]
y5 = [3.457146,3.453541,3.488934,3.561058,3.505991]
y6 = [2.981594,3.013847,3.034028,2.987608,2.990561]
y7 = [2.639756,2.648530,2.653340,2.681929,2.630449]
y8 = [2.431151,2.520134,2.427597,2.419387,2.491999]
y9 = [2.228663,2.245518,2.526316,2.254806,2.248584]
y10 = [2.346557,2.173067,2.222873,2.720044,2.243236]
y11 = [3.346043,3.907393,2.992920,3.222724,3.374086]
y12 = [8.433672,7.642988,5.804389,6.014170,6.733399]
y13 = [10.588490,9.311186,11.609891,10.055348,9.277651]
y14 = [11.775675,12.342624,12.541131,10.849589,11.502887]
y15 = [11.500328,11.510724,13.497233,12.108837,12.692613]
y18 = [11.868486,14.247735,10.105452,10.736072, 19.244870]
y20 = [18.038366,20.622713,15.852278,13.075311,16.553518]
y24 = [31.696767,29.158300,26.844529,22.554951,24.329346]
y28 = [50.035286,51.971386,96.841793,86.994247,71.128859]

y_graph = [np.average(y0),
           np.average(y1),
           np.average(y2),
           np.average(y3),
           np.average(y4),
           np.average(y5),
           np.average(y6),
           np.average(y7),
           np.average(y8),
           np.average(y9),
           np.average(y10),
           np.average(y11),
           np.average(y12),
           np.average(y13),
           np.average(y14),
           np.average(y15),
           np.average(y18),
           np.average(y20),
           np.average(y24),
           np.average(y28)
          ]


# Create traces
trace0 = go.Scatter(
    x = x0,
    y = y_graph,
    mode = 'lines+markers',
    name = 'r = vM (Default)',
    error_y=dict(
        type='data',
        array=[
              np.std(y0),
              np.std(y1),
              np.std(y2),
              np.std(y3),
              np.std(y4),
              np.std(y5),
              np.std(y6),
              np.std(y7),
              np.std(y8),
              np.std(y9),
              np.std(y10),
              np.std(y11),
              np.std(y12),
              np.std(y13),
              np.std(y14),
              np.std(y15),
              np.std(y18),
              np.std(y20),
              np.std(y24),
              np.std(y28)
              ],
        visible=True
    )
)

data = [trace0]
layout=go.Layout(height=1000,
                 title="Local: Time to run vs Number of nodes", 
                 xaxis={'title':'Number of Nodes'}, 
                 yaxis={'title':'Time(sec)'})

figure=go.Figure(data=data,layout=layout)
py.iplot(figure, filename='Opt-Node')
```




<iframe id="igraph" scrolling="no" style="border:none;" seamless="seamless" src="https://plot.ly/~cogle/39.embed" height="1000px" width="100%"></iframe>



<div>
    <a href="https://plot.ly/~cogle/39/" target="_blank" 
       title="OpenMP: Time to run vs Optimization" 
       style="display: block; text-align: center;">
       
        <img src="https://plot.ly/~cogle/39.png" alt="OpenMP: Time to run vs Optimization" 
             style="max-height:1000"  
             onerror="this.onerror=null;this.src='https://plot.ly/404.png';" />
    </a>
    <script data-plotly="cogle:39"  src="https://plot.ly/embed.js" async></script>
</div>


```python
import plotly.plotly as py
import plotly.graph_objs as go
from plotly.tools import FigureFactory as FF 

import numpy as np

x0 = ['500', '1000', '1500' ,'2000', 
      '2500', '3000', '3500',
      '4000','4500','5000', '5500']

#CPU events registered, pulled from results folder

#500
y0 = [0.754536,0.780961,0.720167,0.722796,0.728719]
#1000
y1 = [2.487894,2.525679,2.460646,2.530856,2.502104]
#1500
y2 = [5.488356,5.437134,5.468472,5.440266,5.386134]
#2000
y3 = [9.825435,9.825925,9.772578,9.783777,9.861796]
#2500
y4 = [14.807725,14.809582,14.827138,14.854683,14.773222]
#3000
y5 = [21.040358,21.183004,21.056404,21.206178,21.060265]
#3500
y6 = [28.775791,28.746641,28.638563,28.725114,28.669959]
#4000
y7 = [37.335898,37.876994,37.331223,37.366485,37.370607]
#4500
y8 = [48.383896,47.186651,47.243648,48.305108,48.533143]
#5000
y9= [58.250739,58.166871,58.141610,58.144949,58.189363]
#5500
y10= [70.246207, 70.195268,0.274872, 70.276263,70.331004]

y_graph = [np.average(y0),
           np.average(y1),
           np.average(y2),
           np.average(y3),
           np.average(y4),
           np.average(y5),
           np.average(y6),
           np.average(y7),
           np.average(y8),
           np.average(y9),
           np.average(y10)
          ]


# Create traces
trace0 = go.Scatter(
    x = x0,
    y = y_graph,
    mode = 'lines+markers',
    name = 'r = vM (Default)',
    error_y=dict(
        type='data',
        array=[
              np.std(y0),
              np.std(y1),
              np.std(y2),
              np.std(y3),
              np.std(y4),
              np.std(y5),
              np.std(y6),
              np.std(y7),
              np.std(y8),
              np.std(y9),
              np.std(y10)
              ],
        visible=True
    )
)

data = [trace0]
layout=go.Layout(height=1000,
                 title="Local: Time to run vs Number of stars", 
                 xaxis={'title':'Number of Stars'}, 
                 yaxis={'title':'Time(sec)'})

figure=go.Figure(data=data,layout=layout)
py.iplot(figure, filename='Opt-Stars')
```




<iframe id="igraph" scrolling="no" style="border:none;" seamless="seamless" src="https://plot.ly/~cogle/41.embed" height="1000px" width="100%"></iframe>



<div>
    <a href="https://plot.ly/~cogle/43/" target="_blank" 
       title="OpenMP: Time to run vs Optimization" 
       style="display: block; text-align: center;">
       
        <img src="https://plot.ly/~cogle/43.png" alt="" 
             style="max-height:1000"  
             onerror="this.onerror=null;this.src='https://plot.ly/404.png';" />
    </a>
    <script data-plotly="cogle:43"  src="https://plot.ly/embed.js" async></script>
</div>


```python

```
