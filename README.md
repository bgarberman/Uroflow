# Uroflow

The In Home & Office Uroflowmetry Device, which has been nicknamed “Uroflow”, is an ongoing project with the pediatric urology department at the Children’s Hospital of Philadelphia. The goal is this project is to help combat lower urinary tract dysfunction in children.

This repository contains the prototype device's firmware, which reads, filters, processes, and transmits the data. The processor used is an ATMega32u4. It also contains the files used to test the device, which simulate various typical uroflows from patients with a water pump.

The pin connections are as follows, for use with ATMega32u4: 
    
        Valve open pin = PB1
        Valve close pin = PB2
        Flush button input pin = PC7 (ICP3)
        Pressure sensor output = ADC0
