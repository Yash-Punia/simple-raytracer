#Calls the build console app to run
import subprocess

prj_name = "raytracer"

subprocess.call(["powershell", "-Command", "_bin/Debug/{}.exe".format(prj_name, prj_name)])