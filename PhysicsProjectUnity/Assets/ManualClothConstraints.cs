using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ManualClothConstraints : MonoBehaviour
{
    Cloth cloth;

    ClothSkinningCoefficient[] coes;
    void Start()
    {
        cloth = GetComponent<Cloth>();
        coes = cloth.coefficients;
    }

    int co = 10;
    bool stuck = false;
    bool sticking = false;
    bool switchingcoes = true;
    float timer = 0;
    void Update()
    {
        for (int i = 0; i < coes.Length; i++)
        {
            if (coes[i].maxDistance != cloth.coefficients[i].maxDistance)
            {
                Debug.Log("Coefficient " + i + " : new maxDistance is " + cloth.coefficients[i].maxDistance);
                coes[i].maxDistance = cloth.coefficients[i].maxDistance;
            }
        }

        if (Input.GetKeyDown(KeyCode.L))
        {
            switchingcoes = true;
        }

        if (switchingcoes && timer > 0.01f)
        {
            if (stuck)
            {
                coes[co].maxDistance = Mathf.Infinity;
                co++;
            }
            else
            {
                coes[co].maxDistance = 0;
                co++;
            }

            if (co > 120)
            {
                stuck = !stuck;
                co = 21;
                switchingcoes = false;
            }

            cloth.coefficients = coes;
            timer = 0;
        }
        timer += Time.deltaTime;



        //if (stick)
        //{
        //    Debug.Log(cloth.coefficients[co].maxDistance);
        //    cloth.coefficients[co].maxDistance = Mathf.Infinity;
        //    Debug.Log(cloth.coefficients[co].maxDistance);

        //    co++;
        //    if (co > 120) co = 10;
        //}
        //else
        //{
        //    Debug.Log(cloth.coefficients[co].maxDistance);
        //    cloth.coefficients[co].maxDistance = 0;
        //    Debug.Log(cloth.coefficients[co].maxDistance);

        //    co++;
        //    if (co > 120) co = 10;
        //}
    }
}

//0, 10, 110, 120
