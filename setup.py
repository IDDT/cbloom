from setuptools import setup, Extension
from os import path


README_FP = path.join(path.dirname(__file__), 'README.md')


setup(
    name = 'cbloom',
    version = '0.0.1a5',
    author='IDDT',
    author_email='IDDT@users.noreply.github.com',
    url='https://github.com/IDDT/cbloom',
    description = 'Compact bloom filter.',
    long_description=open(README_FP, 'rt').read(),
    long_description_content_type='text/markdown',
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: Unix',
        'Programming Language :: C',
        'Topic :: Software Development :: Libraries',
    ],
    license='MIT',
    ext_modules = [
        Extension(
            'cbloom',
            sources=[
                'src/hashes.c',
                'src/m_cbloom_methods.c',
                'src/m_cbloom.c',
                'src/t_bloom.c'
            ],
            libraries=['z']
        )
    ]
)
