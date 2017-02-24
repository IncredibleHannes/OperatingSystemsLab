package main.java;

import java.util.*;

public class SiebDesEratosthenes {

    private int n;

    public static void main(String[] args) {
        int n = 0;
        try {
            if(args.length == 1) {
                n = Integer.parseInt(args[0]);
            } else {
                //read from console
                System.out.println("Bis zu welcher oberen Grenze sollen Primzahlen berechnet werden?");
                Scanner scanner = new Scanner(System.in);
                n = Integer.parseInt(scanner.next());
            }

            if(n < 2) throw new IllegalArgumentException("illegal input");
        } catch (Exception e) {
            System.out.println("Falsche Eingabeparameter - Bitte eine Ganzzahl (>=2) eingeben");
            System.exit(1);
        }

        SiebDesEratosthenes sde = new SiebDesEratosthenes(n);
    }



    public SiebDesEratosthenes(int n) {
        Worker test = new Worker(n, 2);
        test.start();
        for(int i = 2; i <= n+1; i++){
            test.values.add(i);
        }
        test.values.parentStopped = true;

    }



    private class Worker extends Thread{
        private Worker child;
        private int n;
        private int prime;
        Pipeline values;


        Worker(int n, int prime){
            this.n = n;
            this.prime = prime;
            values = new Pipeline();
        }


        @Override
        public void run() {
            while(!values.parentStopped || !values.isEmpty()){
                this.checkValue();
            }

            System.out.print( prime + ", ");

            if(child != null){

                child.values.parentStopped = true;
                synchronized (child.values){
                    child.values.notifyAll();
                }
            }
        }


        private void checkValue() {
            int k =values.getNext();

            if(k <= n && k != -1) {
                if (k % prime != 0) {
                    if (child == null) {
                     //   System.out.println("child spawned: " + k);
                        child = new Worker(n, k);
                        child.start();
                    } else {//(Math.pow(k, 2) < n)
                        child.values.add(k);
                    }
                }
            }else{
                this.end();
            }
        }

        void end(){

            if(child != null){
                synchronized (child.values){
                    child.values.parentStopped = true;
                    child.values.notifyAll();
                }
            }
        }

    }

    private class Pipeline{
        private ArrayDeque<Integer> elements = new ArrayDeque<>();
        public boolean parentStopped = false;

        synchronized int getNext(){
            while(elements.isEmpty() && !parentStopped ){
                try {
                    wait();
                }catch (InterruptedException e){
                    e.printStackTrace();
                }
            }
            if(!elements.isEmpty()){
                return elements.poll();
            } else {
              return -1;
            }
        }

        synchronized void add(int newVal){
            elements.add(newVal);
            notifyAll();
        }

        boolean isEmpty(){
            return elements.isEmpty();
        }

    }

}