/**
 * @file nameGenerator.java
 * This sample application permits to randomly select a given name. The source code of this
 * application has been generated by excelExporter, version 1.0.5.
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* Interface of class nameGenerator
 *   main
 */

import java.util.*;


/**
 * Define two lists of male and female given names and offer a simple interface to select a
 * name randomly.
 */
public class nameGenerator
{
    /** The array of female names. */
    static private String[] femaleNameAry =
        { "Adel", "Adriana", "Agnese", "Agnieszka", "Alexandra", "Andrea",
          "Angela", "Angelika", "Anika", "Anja", "Anke", "Anna", "Anne",
          "Anni", "Asifa", "Asma", "Astrid", "Barbara", "Beata", "Beilei",
          "Bianca", "Birgit", "Birgitta", "Britta", "Brigitte", "Christa",
          "Christiane", "Christin", "Christina", "Christine", "Claire", "Claudia",
          "Cornelia", "Cynthia", "Dagmar", "Daniela", "Diana", "Doris", "Edjona",
          "Elena", "Elisabeth", "Elke", "Ester", "Eva - Maria", "Eva-Maria",
          "Fabienne", "Fadwa", "Frauke", "Gabi", "Gerda", "Gisela", "Giselle",
          "Grit", "Gudrun", "Hanane", "Hanna", "Heike", "Helene", "Herta",
          "Ilona", "Ingeborg", "Ingrid", "Inke", "Inken", "Isabella", "Jasmin",
          "Jessica", "Judith", "Julia", "Justa", "Jutta", "Karolin", "Katja",
          "Kattia", "Kerstin", "Kim", "Kirsten", "Kirstin", "Joy-Denise",
          "Lucia", "Magdalena", "Manuela", "Mareike", "Margret", "Maria",
          "Marianne", "Marinela", "Marita", "Melanie", "Merle", "Miao", "Miriam",
          "Monika", "Nadine", "Natalia", "Natalie", "Nathalie", "Nicole",
          "Nima", "Nina", "Notburga", "Olga", "Paulina", "Petra", "Ramona",
          "Regina", "Renate", "Sabine", "Sabrina", "Sandra", "Sarah", "Sarah-Alexandra",
          "Saskia", "Semra", "Sharareh", "Sheela", "Shuang", "Silja", "Silke",
          "Silvia", "Simone", "So-Yun", "Sonia", "Sonja", "Stefanie", "Stephanie",
          "Susanna", "Susanne", "Svetlana", "Swetlana", "Sylvia", "Tanja",
          "Tatjana", "Theresa", "Tolga", "Ulrike", "Ursula", "Ute", "Valentine",
          "Valeriy", "Vera", "Verena", "Winata", "Yi-Chu", "Yvonne", "Yunyu",
         
        };

    /** The array of male names. */
    static private String[] maleNameAry =
        { "Abbas", "Abdalhameed", "Abdelkader", "Abdul", "Abdullah", "Abhay",
          "Abhijeet", "Abhishek", "Achim", "Adam", "Adrian", "Akshay", "Alain",
          "Alan", "Albert", "Albert-Wilfried", "Alberto", "Alex", "Alexander",
          "Alexey", "Alf", "Alfred", "Ali", "Ali Emre", "Alkan", "Alwin",
          "Amol", "Anand", "Anatoli", "Andre", "Andreas", "Andres", "Andrew",
          "Andrzej", "André", "Andy", "Ansgar", "Anton", "Antonio", "Antonius",
          "Apostolos", "Ardo", "Arman", "Armin", "Arnaud", "Arne", "Aron",
          "Artur", "Ashish", "Aswin", "Axel", "Aymeric", "Bachar", "Bahar",
          "Bahman", "Bahri", "Bakir", "Baran", "Baris", "Barkin", "Bart",
          "Bartosch", "Bartosz", "Bas", "Bastian", "Benedikt", "Benjamin",
          "Bennet", "Benno", "Benying", "Bernd", "Bernhard", "Bert", "Bertold",
          "Bertrand", "Bjoern", "Bjorn", "Björn", "Björn Olaf", "Borco",
          "Boris", "Bram", "Bruno", "Bülent", "Burghard", "Burkhard", "Can",
          "Carl", "Carl Friedrich", "Carlos", "Carolus", "Carsten", "Cedric",
          "Chakib", "Charbel", "Charles", "Chen", "Chris", "Christian", "Christof",
          "Christoph", "Christophe", "Christopher", "Chuanxin", "Claude",
          "Claus", "Claus-Dieter", "Claus-Hartmut", "Clemens", "Coen", "Cornelius",
          "Daechul", "Damian", "Daniel", "Danny", "Daqi", "Darius", "Dave",
          "David", "Davide", "Davy", "Dawid", "Deepak", "Dejan", "Denis",
          "Deniss", "Deniz", "Dennis", "Derek", "Detlef", "Dieter", "Dietmar",
          "Dietmar Ulrich", "Dimitri", "Dincer", "Dipak", "Dirk", "Dmitry",
          "Dominik", "Dragan", "Duilio", "Edgar", "Edmund", "Eduard", "Eduardo",
          "Edward", "Edwin", "Ehab", "Eike", "El", "Elmar", "El Mustapha",
          "Emanuele", "Emir", "Emre", "Ender", "Endymion", "Enis", "Enno",
          "Enrico", "Erdal", "Eric", "Erik", "Erman", "Ernst", "Ernst-Jürgen",
          "Erol", "Ertugrul", "Erwann", "Erwin", "Esad", "Etienne", "Eugen",
          "Ewald", "Fabian", "Fakhar", "Falk", "Fang", "Farhad", "Faruk",
          "Fatehjeet", "Fausto", "Felix", "Feng", "Florian", "Francesco",
          "Frank", "Franko", "Franz", "Franz - Josef", "Franz - Reiner",
          "Franz-Gerd", "Franz-Josef", "Franz-Reiner", "Frederic", "Frederik",
          "Friedhelm", "Friedrich Wilhelm", "Gary", "Georg", "Georges", "Georgios",
          "Gerald", "Gerd", "Gerrit-Johannes", "Gert-Jan", "Gereon", "Gerhard",
          "Gernot", "Gerold", "Gerrit", "Gerson", "Gert-Dieter", "Giesberts",
          "Giorgio", "Glen", "Glenn", "Goetz", "Gonzalo", "Goran", "Gordon",
          "Gosse", "Gregor", "Gregory", "Grgur", "Guenter", "Guenther", "Guersel",
          "Guido", "Guillaume", "Gunnar", "Gunter", "Gunther", "Götz", "Günter",
          "Günther", "Gürsel", "Haitham", "Hakan", "Hakim", "Hannes", "Hans",
          "Hans-Dieter", "Hans-Georg", "Hans-Joerg", "Hans-Juergen", "Hans-Jörg",
          "Hans-Jürgen", "Hans-Martin", "Hans-Peter", "Haralambos", "Harald",
          "Harsh", "Hartmut", "Hartwig", "Hayrettin", "Heijen", "Heiko",
          "Heinrich", "Heinz", "Heinz-Dieter", "Heinz-Leo", "Heinz-Peter",
          "Heinz-Willi", "Helge", "Helmut", "Helmuth", "Hendraji", "Hendrik",
          "Hendrikus", "Henning", "Herbert", "Heribert", "Hermann", "Hermann-Josef",
          "Hervais", "Herve", "Holger", "Hongshun", "Horst", "Hrishikesh",
          "Hubert", "Hubertus", "Ibrahim", "Igor", "Ihsan", "Imad", "Iman",
          "Imre", "Inanc", "Ingmar", "Ingo", "Ingolf", "Ioanis", "Ioannis",
          "Irfan", "Isicio", "Ivaylo", "Jacek", "Jack", "Jacques", "Jakob",
          "Jakub", "Jan", "Jan-Erik", "Jan-Philipp", "Jannis", "Janosch",
          "Jarno", "Jaroslaw", "Jasper", "Jean-Babtiste", "Jean-Charles",
          "Jean-Etienne", "Jeffry", "Jens", "Jens Holger", "Jeremie", "Jeremy",
          "Jeroen", "Jerome", "Jialin", "Jian", "Jianfeng", "Jianhua", "Jianpeng",
          "Jiju", "Jim", "Jimmy", "Jingyue", "Joachim", "Job", "Jochen",
          "Joep", "Joerg", "Joern", "Johan", "Johann", "Johannes", "John",
          "Jonas", "Jörg", "Jörn", "Joschka", "Jose", "Josef", "Joseph",
          "Joseph A.", "Josip", "Juergen", "Julian", "Julien", "Jürgen",
          "Kai", "Kai Uwe", "Karim", "Karl", "Karl-Heinz", "Karlheinz", "Karsten",
          "Karthikeyan", "Kenneth", "Kemal", "Kevin", "Kexun", "Khalil",
          "Kittisak", "Klaus", "Klaus-Dieter", "Knut", "Kobe", "Kolja", "Konrad",
          "Konstantin", "Konstantinos", "Lars", "Laszlo", "Laurent", "Leif",
          "Lennart", "Leo", "Leonhard", "Lex", "Li", "Liang", "Loic", "Lokesh",
          "Lothar", "Louis", "Luc", "Lucas", "Ludger", "Ludovic", "Lukas",
          "Lukasz", "Lutz", "Lutz-Josef", "Maarten", "Macin", "Mahesh", "Mahmood",
          "Maik", "Malak", "Malte", "Mandar", "Manfred", "Manuel", "Marc",
          "Marc-Andre", "Marcel", "Marcell", "Marcello", "Marcin", "Marco",
          "Marcus", "Mario", "Marius", "Mariusz", "Mark", "Marko", "Markus",
          "Martin", "Marvin", "Masood", "Massoud", "Masud", "Mateusz", "Mathias",
          "Matteo", "Matthias", "Maurice", "Max", "Maximilian", "Mehmet",
          "Mei", "Meik", "Merdan", "Mert", "Mesut", "Methap", "Michael",
          "Michal", "Michel", "Michele", "Miguel", "Mikhail", "Mike", "Miquel",
          "Mirco", "Mirko", "Miroslaw", "Mohamed", "Mohammad", "Mohammed",
          "Mohit", "Moritz", "Mourad", "Mubashir", "Murat", "Mustafa", "Nabil",
          "Nadim", "Naser", "Nataraj", "Naveen", "Nemr", "Niclaas", "Nico",
          "Nicolas", "Niels", "Niklas", "Nikola", "Nikolaos", "Nikolaus",
          "Nils", "Niluefer", "Ning", "Norbert", "Norbert-Josef", "Norman",
          "Normen", "Nsombo", "Nuran", "Nurettin", "Nuri", "Nyanick", "Oemer",
          "Olaf", "Oleg", "Oliver", "Orhan", "Oskar", "Oussama", "Özen",
          "Pablo", "Paer", "Pascal", "Patrick", "Paul", "Paulo", "Pavan",
          "Pavel", "Pawel", "Pedram", "Percin", "Peter", "Phi-Chanh", "Philip",
          "Philipp", "Philippe", "Piero", "Pierre", "Pierre-Emmanuel", "Pieter",
          "Pieter Ferrie", "Pietro", "Piotr", "Premkumar", "Puneet", "Qihui",
          "Radin", "Radoslaw", "Rafael", "Raimund", "Rainer", "Ralf", "Ralph",
          "Ramanathan", "Ramon", "Raphael", "Raul", "Raymund", "Rebin", "Reiner",
          "Reinhold", "Remi", "Remko", "Ren", "Renaud", "Rene", "René", "Reza",
          "Ricardo", "Richard", "Rick", "Rico", "Ringo", "Ritesh", "Rob",
          "Robert", "Roberto", "Roderich", "Rodrigo", "Roger", "Roland",
          "Rolf", "Rolf-Michael", "Roman", "Romuald", "Ron", "Ronny", "Roozbeh",
          "Ruben", "Rudi", "Rudolf", "Rudolfo", "Ruediger", "Rui Filipe",
          "Ruolin", "Ruoyi", "Ruth", "Ruud", "Rüdiger", "Saeed", "Salif",
          "Salomon", "Sami", "San San", "Sankaraiah", "Sascha", "Sebastian",
          "Sebastien", "Secio", "Selim", "Sencer", "Seong-Jin", "Serge",
          "Sergé", "Sergei", "Sergej", "Servais", "Shahrouz", "Sharwari",
          "Shashank", "Shihang", "Slavcho", "Siegfried", "Simon", "Singh",
          "Sitaram", "So-Yun", "Sofian", "Sohejl", "Sören", "Stanislav",
          "Stanislaw", "Stefan", "Stefano", "Steffen", "Stephan", "Stephan-Johannes",
          "Stephane", "Stephanus", "Stephen", "Steve", "Steven", "Stijn",
          "Su", "Suayip", "Sueleyman", "Sumanth", "Sung - Koo", "Sung-Koo",
          "Suresh", "Suvrajit", "Sven", "Sven-Olaf", "Swapnil", "Swen", "Süleyman",
          "Tamas", "Taner", "Tao", "Tenzin", "Theo", "Theodor", "Thibaud",
          "Thierry", "Thijs", "Thilo", "Thomas", "Thorsten", "Tianbai", "Tim",
          "Timo", "Timon", "Ting", "Tobias", "Tom", "Tomasz", "Ton", "Torsten",
          "Tristan", "Tsvetan", "Tuelay", "Tülay", "Udo", "Uemit", "Ufuk",
          "Ulrich", "Uwe", "Vadim", "Vahideh", "Valentin", "Vasileios", "Veit",
          "Velko", "Veton", "Vijay", "Vikas", "Viktor", "Vincenzo", "Vinicio",
          "Vipul", "Vitali", "Vivek", "Volker", "Waldemar", "Walter", "Wei",
          "Werner", "Wilfried", "Wim", "Winfried", "Winston", "Wolf-Dieter",
          "Wolfgang", "Wolfram", "Wouter", "Xavier", "Xiangbei", "Xin", "Yan",
          "Yazeed", "Yazid", "Yi", "Ying", "Yingjie", "Yousef", "Yu", "Yuki",
          "Yusuf", "Yuwu", "Yves", "Zaim", "Zbigniew", "Zhan Wei", "Zhonghui",
          "Ömer", "Ümit",
        };

    /** The required random generator. */
    static private Random rndGen = new Random();

    /** The interface to pick one name randomly out of the lists. */
    public static void main(String[] argAry)
    {
        boolean male = false;
        if(argAry.length == 0)
            male = rndGen.nextBoolean();
        else if(argAry.length == 1)
        {
            if(argAry[0].equals("male"))
                male = true;
            else if(argAry[0].equals("female"))
                male = false;
            else
            {
                System.err.println("usage: State either male or female as only argument on"
                                   + " the command line"
                                  );
                System.exit(1);
            }
        }
        else
        {
            System.err.println("usage: State either male or female as only argument on"
                               + " the command line"
                              );
            System.exit(2);
        }

        final String[] nameAry = male? maleNameAry: femaleNameAry;
        System.out.println(nameAry[rndGen.nextInt(nameAry.length)]
                           + " (" + (male? "male": "female") + ")"
                          );
        System.exit(0);

    } /* End of main */

} /* End of class nameGenerator definition. */