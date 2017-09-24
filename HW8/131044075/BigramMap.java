import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Created by sude on 2.1.2017.
 */
public class BigramMap<T> implements Bigram<T>{

    private int dType;
    private int count = 0;
    private Map mymap = new HashMap();

    public BigramMap(int dataType) {

        dType = dataType;
    }

    @Override
    public String toString() {

        StringBuilder stringBuilder = new StringBuilder();

        Set set = mymap.entrySet();

        // Get an iterator
        Iterator i = set.iterator();

        TreeMap<String, Integer> treeMap = new TreeMap<String, Integer>();

        while(i.hasNext()) {
            Map.Entry me = (Map.Entry) i.next();
            Pair<T, T> myPair = (Pair<T, T>) me.getKey();
            treeMap.put((Integer) me.getValue() + "(" + myPair.getKey() + " , " + myPair.getValue() + ") : ", (Integer) me.getValue());
        }


        Set set2 = treeMap.descendingMap().entrySet();
        i = set2.iterator();


        while(i.hasNext()) {
            Map.Entry me = (Map.Entry) i.next();
            String temp = (String) me.getKey();
            String basamak = me.getValue().toString();
            stringBuilder.append(temp.substring(basamak.length()) + (Integer)me.getValue() + "\n");
        }

        return stringBuilder.toString();
    }

    @Override
    public void readFile(String filename) throws myExceptions, IOException {

        String temp = null, tmp;


        BufferedReader br = null;
        br = new BufferedReader(new FileReader(filename));
        temp = br.readLine();
        br.close();


        StringTokenizer st = new StringTokenizer(temp);
        count = st.countTokens();

        //if(count==0)
        //  throw myExceptions("Empty Document");

        if(count==0)
            throw new myExceptions("Exception: Empty Document");

        if(dType==1)
        {

            int convertString;
            for(int j=0; j<temp.length() ; ++j)
            {
                convertString = temp.charAt(j)-'0';
                if(!((convertString>=0 && convertString<=9 ) || temp.charAt(j)==' ') )
                    throw new myExceptions("Wrong data type");
            }

        }


        if(dType == 3)
        {
            int convertString;
            for(int i=0; i<temp.length() ; ++i){
                convertString = temp.charAt(i)-'0';
                if(!((convertString>=0 && convertString<=9 )|| temp.charAt(i)=='.' || temp.charAt(i)==' '))
                    throw new myExceptions("Wrong data type");
            }
        }



        String[] arr = temp.split(" ");
        String word1, word2;

        word1 = arr[0];

        for (int i=1; i<arr.length; i++) {

            word2 = arr[i];
            Pair<T, T> first = new Pair<T, T>((T)word1, (T)word2);
//            Set set = mymap.entrySet();
//            Iterator ite = set.iterator();
//            while(ite.hasNext()) {

//            Map.Entry me = (Map.Entry)ite.next();

            if (mymap.containsKey(first))
                mymap.put(first, (Integer) mymap.get(first) + 1);
            else
                mymap.put(first, 1);
//            }
            word1 = word2;

        }
    }


    public void yazdir(){

        System.out.println("map size " + mymap.size()  );

        Set set = mymap.entrySet();

        // Get an iterator
        Iterator i = set.iterator();

        // Display elements
        while(i.hasNext()) {
            Map.Entry me = (Map.Entry)i.next();
            System.out.print(me.getKey() + ": ");
            System.out.println(me.getValue());
        }
        System.out.println();
    }

    @Override
    public int numGrams() {

        return count-1;
    }

    @Override
    public int numOfGrams(T firstElement, T secondElement) {

        Pair<T, T> first = new Pair<T, T>(firstElement, secondElement);
        Set set = mymap.entrySet();
        Iterator i = set.iterator();

        // Display elements
        while(i.hasNext()) {
            Map.Entry me = (Map.Entry)i.next();
            Pair<T,T> second = (Pair<T,T>)me.getKey();
            T fElement = second.getKey();
            T sElement = second.getValue();

            if(fElement.toString().equals(firstElement.toString()) && sElement.toString().equals(secondElement.toString()))
                return((Integer)me.getValue());
        }

        return 0;
    }
}
