package edu.nuist.zenia.util;

import java.io.*;
import java.nio.charset.StandardCharsets;

public class FileUtil {

	public static void processInLine(InputStream is, LineProcess lp){
		String line = "";
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(is, "utf-8"));
			line = br.readLine();
			while (line != null)
			{
				
				lp.doLine(line);
				line = br.readLine();
			}
			br.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch(Exception e){
			System.out.println( line );
		}
		
	}

	public static void processInLine(String data, LineProcess lp){
		String line = "";
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(data), "utf-8"));
			line = br.readLine();
			while (line != null)
			{
				
				lp.doLine(line);
				line = br.readLine();
			}
			br.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch(Exception e){
			System.out.println( line );
		}
		
	}
	public static void writeStringToFile(String str, String fileName){
		File f = new File(fileName);
		try {
		    if(!f.exists()){
		    	f.createNewFile();
		    }
		    FileWriter fw = new FileWriter(f, StandardCharsets.UTF_8);
		    BufferedWriter out = new BufferedWriter(fw);
		    out.write(str, 0, str.length());
		    out.close();
		}catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static String getFileContent(String targetFile){	
		BufferedReader br = null;
	    try{	    	
		    String data = "";
		    String jsonString = "";
		    InputStreamReader isr = new InputStreamReader(new FileInputStream(targetFile), StandardCharsets.UTF_8);
	    	br = new BufferedReader(isr);  
		    data = br.readLine();
		    jsonString += data;
		    while( data != null){ 
		        data = br.readLine();
		        if(data != null) jsonString += data;
		    }  		
		    if("".equals(jsonString))
		    	return null;
		    else
		    	return jsonString.trim();
	   }catch(IOException e){
			//logger.error(" FileIOException getJSONFromFile - get JSON from the file : "+ targetFile + " IOException");
		}finally{
			if(br != null)
				try{
					br.close();
				}catch(IOException e){;}
		}	    
	    return null;
	} 

}
