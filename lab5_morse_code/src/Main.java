import java.io.*;
import java.lang.StringBuilder;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args){

        Scanner in = new Scanner(System.in);
        String command = in.next().toLowerCase(Locale.ROOT);
        String inputFileName = in.next().toLowerCase(Locale.ROOT);
        ArrayList<String> input;


        // reading file
        Reader reader = null;
        try{
            reader = new InputStreamReader(new FileInputStream(inputFileName));
            // read
        }
        catch (IOException e) {
            System.err.println("Error while reading file: " + e.getLocalizedMessage());
        }
        finally{
            if(reader != null){
                try{
                    reader.close();
                }
                catch(IOException e){
                    e.printStackTrace(System.err);
                }
            }
        }

        // read command and file name from console, start encoder or decoder
        if(command.equals("decode")){
            MorseDecoder decoder = new MorseDecoder(inputFileName);
            decoder.decode("result.txt");
        }
        else if(command.equals("code")){
            MorseEncoder encoder = new MorseEncoder(inputFileName);
            encoder.encode("result.txt");
        }
    }
}
