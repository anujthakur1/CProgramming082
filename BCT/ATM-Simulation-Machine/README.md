<h1>ATM Simulation Machine</h1>

<p>This is a simple command-line ATM Simulation Machine written in C. This project was developed as part of the ACES C-Project Demonstration.</p>

<h2>Team Members </h2>
<ul>
  <li>Bishal Dahal</li>
  <li>AayushnNeupane</li>
  <li>Pranjal Dahal</li>
  <li>Paritosh Ghimire</li>
</ul>

<h2>Features</h2>
<ul>
        <li><strong>Account Management:</strong> Create, login, and manage user accounts securely.</li>
        <li><strong>Transaction Features:</strong> Deposit, withdraw, and check balance.</li>
        <li><strong>Security Features:</strong> Secure PIN entry, failed login attempt tracking, and logging.</li>
        <li><strong>Logging:</strong> Transactions and security events are logged.</li>
    </ul>
    

 <h2>Installation</h2>
    <p><strong>Step 1:</strong> Clone the repository</p>
    <pre><code>git clone https://github.com/your-username/ATM-System.git</code></pre>
    
  <p><strong>Step 2:</strong> Compile the program</p>
    <pre><code>gcc atm.c -o atm</code></pre>

  <p><strong>Step 3:</strong> Run the program</p>
   <pre><code>./atm</code></pre>

  <h2>Usage</h2>
    <p>After running the program, you can:</p>
    <ul>
        <li>Create an account</li>
        <li>Login and perform transactions</li>
        <li>Change PIN or delete an account</li>
        <li>View transaction and security logs</li>
    </ul>

    
  

   <h2>Security & Logging</h2>
    <ul>
        <li>Failed login attempts are recorded in <code>security.log</code>.</li>
        <li>Each transaction (deposit/withdrawal) is logged in <code>transactions.log</code>.</li>
    </ul>
