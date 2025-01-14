fun cd (s:string):unit = OS.FileSys.chDir (s);
fun pwd ():string = OS.FileSys.getDir ();
fun ls ():Word32.word = OS.Process.system "dir";
