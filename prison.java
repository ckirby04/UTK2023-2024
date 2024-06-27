// Prison Program, 9/10/2023
// Clark Kirby, COSC 101 Stephen Marz
/*
https://www.geeksforgeeks.org/scanner-nextdouble-method-in-java-with-examples/
https://www.baeldung.com/java-printstream-printf
https://stackoverflow.com/questions/14470372/use-printf-with-multiple-variables-in-java
*/

import java.util.Scanner;

class prison{

    public static void main(String[] args) {

        Scanner scan = new Scanner(System.in);

        System.out.print("Enter client's first name: ");
        String fname = scan.next();

        System.out.print("Enter client's last name: ");
        String lname = scan.next();

        System.out.print("Enter client's age: ");
        int age  = scan.nextInt();

        System.out.print("Enter client's prison sentence in months: ");
        Double sentence  = scan.nextDouble();
        sentence /= 12; //simply converts the sentence that was taken in months to years, maintains the decimal we need for later bc its a double.

        scan.close(); //just a note for myself, always close the scanner.

        double agePostPrison = age + sentence; // age post prison will be the current age of the prisoner plus the sentence that is now in years and wil give us a double of the age that our prisoner will be post sentence 

        //                      last name, first name, currenlty age years old, will be age(to two deicmal places) when released from prison.  
        System.out.printf("%s, %s, currently %d years old, will be %.2f when released from prison. %n", lname, fname, age, agePostPrison);

    }


}