package main.java;

import java.util.Scanner;

public class SiebDesEratosthenes {

    private int n;

    public static void main(String[] args) {
        int n = 0;
        if(args.length == 1) {
            n = Integer.parseInt(args[0]);
        } else {
            //read from console
            System.out.println("Bis zu welcher oberen Grenze sollen Primzahlen berechnet werden?");
            Scanner scanner = new Scanner(System.in);
            n = Integer.parseInt(scanner.next());
        }
        SiebDesEratosthenes sde = new SiebDesEratosthenes(n);
    }



    public SiebDesEratosthenes(int n) {
        System.out.println("current n: " + n);
        //todo do sth
    }
}