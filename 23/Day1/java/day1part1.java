import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Program for Advent of Code 2023 Day 1 Part 1.
 * Takes the first and last digit from a string and creates a single two-digit 
 * number from them, then adds that number to a running total.
 * 
 * @author Harley Coughlin
 */
public class day1part1 {

    /**
     * Takes the ASCII reprentation from the twoDigitConversion method and returns the digit.
     *
     * @param asciiNumber The ASCII number returned by the .charAt method
     * @return digit
     * @see #twoDigitConversion(String nextLine)
     */
    public static int asciiToInt(int asciiNumber) {
        int digit = 0;
        switch (asciiNumber) {
            case 48:
                digit = 0;
                break;
            case 49:
                digit = 1;
                break;
            case 50:
                digit = 2;
                break;
            case 51:
                digit = 3;
                break;
            case 52:
                digit = 4;
                break;
            case 53:
                digit = 5;
                break;
            case 54:
                digit = 6;
                break;
            case 55:
                digit = 7;
                break;
            case 56:
                digit = 8;
                break;
            case 57:
                digit = 9;
                break;
        }
        return  digit;
    }

    /**
     * Searches a string for the first and last digit and creates a two digit number.
     * Calls asciiToInt to convert from char to int.
     *
     * @param nextLine String input from main.
     * @return twoDigit
     * @see #asciiToInt(int asciiNumber)
     */
    public static int twoDigitConversion(String nextLine) {
        int length = nextLine.length();
        int twoDigit = 0;
        int num1 = 0, num2 = 0; 
        int num1pos = length;
        boolean num2found = false;

        for (int i = 0; i < length; ++i) {
            if (Character.isDigit(nextLine.charAt(i)) && i <= num1pos) {
                num1 = asciiToInt(nextLine.charAt(i));
                num1pos = i;
            } else if (Character.isDigit(nextLine.charAt(i))) {
                num2 = asciiToInt(nextLine.charAt(i));
                num2found = true;
            }
        }
        if (!num2found) {
            num2 = num1;
        }
        twoDigit = (num1 * 10) + num2;
        return twoDigit;
        }

    /**
     * Calls twoDigitConversion to convert digits inside a string from a text file called text
     * into a two digit number, adds it to a running total, and then prints the total
     *
     * @see #twoDigitConversion(String nextLine)
     * @throws FileNotFoundException if file isn't located in the same folder
     */
    public static void main(String[] args) {
        
        int total = 0;
        try {
            File text = new File("../file.txt");
            Scanner scnr = new Scanner(text);
            String nextLine = "";
            while (scnr.hasNextLine()) {
                nextLine = scnr.nextLine();
                total += twoDigitConversion(nextLine);
            }
            scnr.close();
        } catch (FileNotFoundException e) {
            System.out.println("error");
            e.printStackTrace();
        }

        System.out.println(total);
    }
}
