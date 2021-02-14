using System;
using System.Collections.Generic;
using SpaceSim;

    class Astromy
    {
        public static void Main(string[] args)
        {

        List<SpaceObject> solarSystem = new List<SpaceObject>();

        {
            Star Sun = new Star("Sun", 0, 0, 60000, 0, "Gold");
            Planet Mercury = new Planet(Sun, "Mercury", 80, 88, 6000, 59, "DimGray");
            Planet Venus = new Planet(Sun, "Venus", 120, 224, 10000, 243, "LemonChiffon");
            Planet Earth = new Planet(Sun, "Earth", 150, 365, 11000, 1, "RoyalBlue");
            Planet Mars = new Planet(Sun, "Mars", 180, 687, 9800, 1.025, "Coral");
            Planet Jupiter = new Planet(Sun, "Jupiter", 240, 20000, 32000, 0.4125, "Peru");
            Planet Saturn = new Planet(Sun, "Saturn", 300, 18000, 30004, 0.417, "DarkKhaki");
            Planet Uranus = new Planet(Sun, "Uranus", 360, 30685, 18000, 0.67, "LightSkyBlue");
            Planet Neptun = new Planet(Sun, "Neptun", 400, 60190, 17000, 0.71, "DodgerBlue");
            Moon Moon = new Moon(Earth, "The Moon", 16, 27.322, 3800, 27, "White");
            Moon Phobos = new Moon(Mars, "Phobos", 10, 0.3189, 3500, 0.3, "GRAY");


            Earth.setChild(Moon);
            Mars.setChild(Phobos);

            solarSystem.Add(Sun);
            solarSystem.Add(Mercury);
            solarSystem.Add(Venus);
            solarSystem.Add(Earth);
            solarSystem.Add(Mars);

            solarSystem.Add(Moon);
            solarSystem.Add(Phobos);
        };

        Console.WriteLine("Enter number of days");
        String Stime = Console.ReadLine();
        int time = Convert.ToInt32(Stime);

        bool match = false;

        Console.WriteLine("Select one of the planets: Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus or Neptun.");
        String answer = Console.ReadLine();

            foreach (SpaceObject obj in solarSystem)
            {
            if(obj.name.Equals(answer))
            {
                match = true;
                obj.Draw();

                if (obj.Orbiting != null)
                {
                    var temp = obj.getPosition(time);
                    double x = temp.Item1;
                    double y = temp.Item2;

                    Console.WriteLine(obj.name + "'s position relative to the sun after " + time + " is:\nx: " + (int) x * 1000000 + " km" + " and y:" + (int) y * 1000000 + " km");
                    Console.WriteLine();
                }

                int storrelse = obj.Children.Count;
                if(storrelse > 0) 
                {  
                    Console.WriteLine("Moons:");
                    Console.WriteLine();
                    foreach (SpaceObject child in obj.Children)
                        {
                            child.Draw();

                            var temp = child.getPosition(time);
                            double x = temp.Item1;
                            double y = temp.Item2;

                            Console.WriteLine(child.name + "'s position relative to the sun after " + time + " is:\nx: " + (int)x * 1000000 + " km" + " and y:" + (int)y * 1000000 + " km");
                        Console.WriteLine();
                    }
                }
            }
            
            }
            if(!match)
        {
            Console.WriteLine("You did not type a planet.");
            Console.WriteLine();
            solarSystem[0].Draw();
            Console.WriteLine();
            foreach (SpaceObject planet in solarSystem)
            {
                if(planet is Planet)
                {
                    planet.Draw();
                    Console.WriteLine();
                }
            }
        }
            Console.ReadLine();
        }
    }
