import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class PartA1 {
   public static void main(String[] args) throws Exception {
       File file = new File("UFOReports.txt");
       FileReader fr = new FileReader(file);
       BufferedReader br = new BufferedReader(fr);

       HashMap<String, Integer> wordFrequencyMap = new HashMap<>();
       Pattern pattern = Pattern.compile("\\b\\w{7,}\\b", Pattern.CASE_INSENSITIVE);

       String line;
       while ((line = br.readLine()) != null) {
           Matcher matcher = pattern.matcher(line);
           while (matcher.find()) {
               String word = matcher.group().toLowerCase();
               wordFrequencyMap.put(word, wordFrequencyMap.getOrDefault(word, 0) + 1);
           }
       }

       String mostFrequentWord = "";
       int maxFrequency = 0;
       for (Map.Entry<String, Integer> entry : wordFrequencyMap.entrySet()) {
           if (entry.getValue() > maxFrequency) {
               mostFrequentWord = entry.getKey();
               maxFrequency = entry.getValue();
           }
       }

       System.out.println("UFOReports.txt: " + mostFrequentWord);
   }
}
