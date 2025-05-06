#!/bin/bash

# Prompt user for the starting balance
read -p "Enter the starting balance: " balance

# Display the menu options
echo "Menu options"
echo "a) Deposit"
echo "b) Withdraw"
echo

# Prompt user for a selection
read -p "Enter your selection: " selection

# Process the selection using a case statement
case $selection in
    a|A) 
        # Handle deposit
        read -p "Enter the deposit amount: " deposit
        ((balance = balance + deposit))
        ;;
    b|B) 
        # Handle withdrawal
        read -p "Enter the withdraw amount: " withdraw
        ((balance = balance - withdraw))
        ;;
    *) 
        # Handle invalid input
        echo "ERROR! Invalid input was provided"
        ;;
esac

# Display the final balance
echo "The final balance is: $balance"
