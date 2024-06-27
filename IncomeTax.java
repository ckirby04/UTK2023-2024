//Income Tax Program, 9/24/2023
// Clark Kirby, Stephen Marz COSC101
// No outside sources used. 

import java.util.Scanner;

class IncomeTax {

    public static void main(String[] args) {

        Scanner scan = new Scanner(System.in);

        System.out.print("Enter total income: $");
        double income = scan.nextDouble();
        scan.close();

        double total_income = income;
        double total_tax = 0.0;

        // Top tax bracket, 38.15 percent above $15,000
        //This algorithm takes only the income that is above the threashold and taxes it at its repsective rate, then it sets the income at everything under the threashold to be taxed at the lower brackets and repeats for every bracket. 
        if(income > 15000){
        total_tax += (income - 15000.00) * 0.3815;
        income = 15000.00;
        }
        
        // Second tax bracket, 31.29 percent above $10,000
        if(income > 10000){
        total_tax += (income - 10000.00) * 0.3129;
        income = 10000.00;
        }

        // Third tax bracket, 28.71 percent above $5,000
        if(income > 5000){
        total_tax += (income - 5000.00) * 0.2871;
        income = 5000.00;
        }

        // Fourth tax bracket, 25 percent above $1,000
        if(income > 1000){
        total_tax += (income - 1000.00) * 0.2500;
        income = 1000.00;
        }

        // Lowest tax bracket, 20 percent from zero to 1,000
        if(income > 0){
        total_tax += (income) * 0.2000;
        }
        // this ensures that if the income is zero or less than zero, it will not set the taxes due at 0 because you cannot owe negative taxes.
        double taxes = 0.0;

        if(total_income > 0){
        taxes = (total_tax/total_income) * 100;
        }


        System.out.printf("Taxes owed = $%.2f%n", total_tax);
        System.out.printf("Final Tax  = %.0f%%%n", taxes);
        
}
}