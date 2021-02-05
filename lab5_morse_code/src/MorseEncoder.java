
import javax.print.attribute.HashAttributeSet;
import java.util.ArrayList;
import java.util.HashSet;

public class MorseEncoder {
    private final Alphabet alphabet;

    public MorseEncoder(Alphabet alphabet){
        this.alphabet = alphabet;
    }

    public void encode(ArrayList<String> text, String resultFileName) throws NullPointerException{

        StringBuilder resultString = new StringBuilder();
        HashSet<StatCounter> statistic = new HashSet<StatCounter>();

        for(String str : text){
            if(str.equals("/n")){
                // напечатать ентер в файл
                resultString.delete(0, resultString.length());
                continue;
            }
            for (Character character : str.toCharArray()){
                resultString.append(alphabet.getMorseCodeByChar(character));
                resultString.append(' ');
                // посчитать в статистику
            }
            resultString.append("    ");
        }

        // вывести результат


        // create stats file int the end
    }

}
