<hr>
<h1 align = "center">
    ATM
</h1>

<p align = "center">
    THIS IS A PRE-DEVELOPLMENT FLOW/DESIGN OF THE ATM PROJECT
</p>

<h2 align = "center">
    BEFORE LOGIN
</h2>

<pre>
    1. Ask user to login/register
    2. If user registers:
        - Get NIC Number
        - Check for existing account (By NIC)
        - If account exists:
            • Terminate registration and ask for login
        - If account doesnot exist:
            • Create account
                - Data needed for account:
                    • A unique ID
                    • Account number (provided by us automatically)
                    • Name
                    • PIN
                    • Total amount in account
            • Ask for login
    3. If user logins:
        - Check for existing account
        - If account exists:
            • Continue to pin code screen
        - If account doesnot exist:
            • Show invalid login message and ask to re login
</pre>
        
<h2 align = "center">
    AFTER LOGIN
</h2>

<pre>
    4. Ask for PIN code
        - If pin code incorrect:
            • Reprompt for pin code input
        - If pin code correct:
            • Continue to menu
    5. Display menu
        - Cash withdrawal
            • Display different amounts (500, 1000, 5000, 10000, 20000, 25000)
            • And a custom input option [range from 500-25000]
            • Max amount can only be 25,000 at a time
            • Check for account balance
                - If balance sufficient:
                    • Deduct balance
                    • Display successful withdrawal (with updated amount in account)
                - If balance insufficient:
                    • Display insufficient balance
                    • Terminate the program
        - Update PIN
            - Ask user for ID
            - Ask user for old PIN
                • If PIN and ID correct
                    - Get updated PIN
                    - Confirm updated PIN
                    - Update and display a success message
                • If PIN and ID incorrect
                    - Display unsuccessful message
                    - Terminate the program
        - Balance check
            • Display balance
        - Delete account
            • PIN confirmation
    6. Display a thankyou message
</pre>

<h1 align = "center">
    ATM
</h1>
<hr>
