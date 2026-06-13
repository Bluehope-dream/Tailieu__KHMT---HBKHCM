# LAB2 - FP

## Bước 1: chạy docker

```sh
docker build -t ltnc-lab2 .

docker run -it --name ltnc-lab2 -v ${PWD}:/app -w /app ltnc-lab2
root@db1cb44673ec:/app# ls
Dockerfile  README.md  Specification.md  solution.py  testcase.py
```

## Bước 2: Chạy test 

```
root@fb4cd81783ed:/app# pytest testcase.py 
================================================================================== test session starts ===================================================================================
platform linux -- Python 3.12.13, pytest-9.0.3, pluggy-1.6.0
rootdir: /app
collected 35 items                                                                                                                                                                       

testcase.py ...................................                                                                                                                                    [100%]

=================================================================================== 35 passed in 0.03s ===================================================================================
```

---

<p align="center">
  <a href="https://www.facebook.com/Shiba.Vo.Tien">
    <img src="https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white" alt="Facebook"/>
  </a>
  <a href="https://www.tiktok.com/@votien_shiba">
    <img src="https://img.shields.io/badge/TikTok-000000?style=for-the-badge&logo=tiktok&logoColor=white" alt="TikTok"/>
  </a>
  <a href="https://www.facebook.com/groups/khmt.ktmt.cse.bku?locale=vi_VN">
    <img src="https://img.shields.io/badge/Facebook%20Group-4267B2?style=for-the-badge&logo=facebook&logoColor=white" alt="Facebook Group"/>
  </a>
  <a href="https://www.facebook.com/CODE.MT.BK">
    <img src="https://img.shields.io/badge/Page%20CODE.MT.BK-0057FF?style=for-the-badge&logo=facebook&logoColor=white" alt="Facebook Page"/>
  </a>
  <a href="https://github.com/VoTienBKU">
    <img src="https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white" alt="GitHub"/>
  </a>
</p>
