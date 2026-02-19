import subprocess
import re
import matplotlib.pyplot as plt
import numpy as np

def run_simulation():
    print("Running simulation (1M events)...")
    process = subprocess.Popen(['./build/rutherford', 'run1.mac'], 
                               stdout=subprocess.PIPE, 
                               stderr=subprocess.STDOUT, 
                               text=True)
    
    counts = {}
    for line in process.stdout:
        match = re.search(r'angle: (\d+) deg, counts: (\d+)', line)
        if match:
            angle = int(match.group(1))
            count = int(match.group(2))
            counts[angle] = count
    
    process.wait()
    return counts

def plot(counts):
    # Sort and filter (only 10-180 deg, 0 deg is the beam)
    angles = sorted([a for a in counts.keys() if 10 <= a <= 180])
    sim_yield = [counts[a] for a in angles]
    
    # Theoretical: 1 / sin^4(theta/2)
    theta_rad = np.radians(angles)
    theory_yield = 1.0 / (np.sin(theta_rad / 2.0)**4)
    
    # Normalize theory to match simulation at 30 deg
    idx_30 = angles.index(30)
    norm_factor = sim_yield[idx_30] / theory_yield[idx_30]
    theory_yield *= norm_factor

    plt.figure(figsize=(10, 6))
    plt.yscale('log')
    plt.plot(angles, sim_yield, 'ko', label='Simulation (Geant4)')
    plt.plot(angles, theory_yield, 'r--', label='Rutherford Formula (normalized)')
    
    plt.xlabel('Angle of deflection (degree)')
    plt.ylabel('Yield (count)')
    plt.title('Rutherford Scattering Yield vs. Angle')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.5)
    
    plt.savefig('results.png', dpi=300)
    print("Plot saved as results.png")

if __name__ == "__main__":
    data = run_simulation()
    if data:
        plot(data)
    else:
        print("No data collected from simulation.")
