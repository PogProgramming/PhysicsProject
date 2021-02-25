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
    bool stick = false;
    void Update()
    {
        for(int i = 0; i < coes.Length; i++)
        {
            if (coes[i].maxDistance != cloth.coefficients[i].maxDistance)
            {
                Debug.Log("Coefficient " + i + " : new maxDistance is " + cloth.coefficients[i].maxDistance);
                coes[i].maxDistance = cloth.coefficients[i].maxDistance;
            }
        }

        if (Input.GetKeyDown(KeyCode.Space))
        {
            //stick = !stick;
            //Debug.Log(stick);
            if (stick)
            {
                for (int i = 0; i < cloth.coefficients.Length; i++)
                {
                    cloth.coefficients[i].maxDistance = 0;
                }
            }
            else
            {
                for (int i = 0; i < cloth.coefficients.Length; i++)
                {
                    cloth.coefficients[i].maxDistance = Mathf.Infinity;
                }
            }
            stick = !stick;
        }

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
