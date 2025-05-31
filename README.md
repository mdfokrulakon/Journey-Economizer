 Project Name: Journey Economizer

Project Description:

Journey Economizer is a comprehensive C++ console application that integrates financial planning with graph-based travel cost analysis. It serves users who aim to plan international trips while staying within a budget, 
by calculating optimal travel costs and suggesting financial strategies to meet their goals.

 Key Features:

1. Travel Cost Estimation using Dijkstra's Algorithm :

   * Models countries as graph nodes with weighted edges representing travel costs.
   * Finds the **shortest path** and **minimum cost** between any two countries.
   * Lists all reachable destinations from a source country within a specified budget.

2. Financial Advisory System :

   * Takes user input for monthly income, income growth rate, fixed and variable expenses.
   * Projects future **monthly savings** over a chosen planning period.
   * Suggests **proportional reductions** in spending to help meet a vacation/travel budget.
   * Saves financial advice and projections to a text file (`financial_advice.txt`).

3. User Interaction and File Output :

   * Easy-to-use console interface with multiple options.
   * Outputs include:

     * Current expense breakdown
     * Projected cash flow
     * Maximum achievable spending reductions
     * Travel cost and path details

 🛠️ Technologies Used:

* **C++ Standard Library** (`<map>`, `<list>`, `<unordered_map>`, `<queue>`, `<fstream>`, `<cmath>`, etc.)
* **Dijkstra's algorithm** for pathfinding
* **File I/O** for saving analysis reports
* **Formatted output** using `<iomanip>`

 Objective:

To empower users with tools for effective financial planning and trip cost optimization, enabling them to reach their travel goals realistically and sustainably.
