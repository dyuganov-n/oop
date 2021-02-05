import java.io.*;
import java.lang.StringBuilder;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        try{
            Scanner in = new Scanner(System.in);
            String command = in.next().toLowerCase(Locale.ROOT);
            String inputFileName = in.next();

            Parser parser = new Parser();

            if(command.equals("decode")){
                MorseDecoder decoder = new MorseDecoder();
                String outputFileName = "decode_result.txt";
                decoder.decode(parser.parseFile(inputFileName), outputFileName);
                System.out.println("Decode completed. Output file: " + outputFileName);
            }
            else if(command.equals("code")){
                String outputFileName = "encode_result.txt";
                MorseEncoder encoder = new MorseEncoder();
                encoder.encode(parser.parseFile(inputFileName), outputFileName);
            }

        }
        catch(Throwable e){
            System.err.println("Error somewhere in program: " + e.getLocalizedMessage());
        }
    }
}
