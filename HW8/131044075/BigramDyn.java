import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * Created by sude on 3.1.2017.
 */
public class BigramDyn<T> implements Bigram<T>{

    private int dType;
    private int capacity;
    private int used;
    private int count = 0;

    private T[] data;

    public BigramDyn(int dataType) {
        dType = dataType;
        capacity = 50;
        used = 0;
        data = (T[]) new Object[capacity];
    }

    public int getdType() {
        return dType;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getUsed() {
        return used;
    }

    public T[] getData() {
        return data;
    }

    public void setdType(int dType) {
        this.dType = dType;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    @Override
    public String toString() {

        StringBuilder stringBuilder = new StringBuilder();
        String[] array = new String[used];
        String tempStr = null;

        for(int i=1; i<used; i++){

            String bigramElement = numOfGrams(data[i-1],data[i]) + " : (" +  data[i-1].toString() + " , " + data[i].toString() + ")" + "\n";
            array[i-1] = bigramElement;
            //stringBuilder.append(array[i-1]);
        }

        for (int i=0; i<used-1; i++)
        {
            for (int j=1; j<used-i-1; j++)
            {
                if(array[j-1].compareTo(array[j]) < 0)
                {
                    tempStr = array [j-1];
                    array [j-1] = array [j];
                    array [j] = tempStr;
                }
            }
        }

        for(int i=1; i<used-1; i++){
            if(!array[i].equals(array[i-1]))
                stringBuilder.append(array[i-1]);
        }
        stringBuilder.append(array[used-2]);


        return stringBuilder.toString();




//        //int max = data[0].second;
//
//        for(int i=0; data[i].second != '\0'; ++i)
//        {
//            if(data[i].second > max)
//            {
//                max=data[i].second;
//                ++i;
//            }
//        }
//
//        for(int i=0; data[i].second != '\0'; ++i)
//        {
//            for(int j=0; data[j].second != '\0'; ++j)
//            {
//                if(data[j].second == max)
//                {
//                    outputStream << data[j].first.first << " " << data[j].first.second
//                            << " = " << data[j].second << endl;
//                }
//            }
//            max--;
//        }
    }

    @Override
    public void readFile(String filename) throws myExceptions, IOException {

        String temp, tmp;
        int foundItemIndex = -1;
        int count=0;

        BufferedReader br = null;
        br = new BufferedReader(new FileReader(filename));
        temp = br.readLine();
        br.close();

        StringTokenizer st = new StringTokenizer(temp);
        count = st.countTokens();

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
        String word1;



        for (int i=0; i<arr.length; i++) {

            if(used<capacity) {
                data[used] = (T) arr[i];
                used++;
            }
            else{
                capacity *= 2;
                T[] tempData = (T[]) new Object[capacity];

                for(int j=0; j<used; j++)
                    tempData[j] = data[j];
                data = null;
                data = (T[]) new Object[capacity];

                for(int j=0; j<used; j++)
                    data[j] = tempData[j];

                data[used] = (T) arr[i];
                tempData = null;
                used++;

            }
        }

    }

    @Override
    public int numGrams() {
        return used-1;
    }

    @Override
    public int numOfGrams(T firstElement, T secondElement) {

        int count = 0;
        T word1, word2;
        word1 = data[0];
        for(int i=1; i<used; i++){

            word2 = data[i];
            if(firstElement.toString().equals(word1.toString()) && secondElement.toString().equals(word2.toString())){
                count++;
            }
            word1 = word2;
        }

        return count;
    }
}
