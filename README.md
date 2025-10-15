# algoritmo de compressão/descompressão de arquivos
## Composto por dois arquivos principais:
- tabela.cpp: recebe uma pasta que contém arquivos .cpp e .h.
  
  -> O objetivo desse arquivo é gerar uma tabela de frequência, indicando símbolos mais usados, da linguagem c++, em projetos. Para isso usamos alguns
  repositórios aleatórios que encontramos no github, como:
  
      - https://github.com/gabime/spdlog?tab=readme-ov-file
      - https://github.com/google/orbit
      - https://github.com/chriskohlhoff/asio
    Além de projetos que fizemos em lp1, chamados "classes abstratas" e "imobiliária", e do "calculo de expressão pós-fixada" de ebd2.
  
    -> Esses arquivos se encontram na pasta codigo e foram importantes para vermos os símbolos que mais aparecem em códigos c++.
  
    obs: a tabela foi salva no arquivo frequencia_huffman.txt, em ordem decrescente e contendo apenas os símbolos cuja frequência é maior que 500.
- huffman.cpp: mapeia os símbolos mais frequentes, de acordo com a tabela, os números narturais e o alfabeto, para códigos binários
  
  -> O objetico desse arquivo é a compressão e a descompressão. Para isso após a compilação do programa, deve-se executá-lo do seguinte modo:
  
        ./huffman -c arquivo_entrada arquivo_saida(bin) para a compressão
        ./huffman -d arquivo_entrada(bin) arquivo_saida para a descompressão
