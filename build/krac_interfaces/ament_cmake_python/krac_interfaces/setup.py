from setuptools import find_packages
from setuptools import setup

setup(
    name='krac_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('krac_interfaces', 'krac_interfaces.*')),
)
